import tkinter as tk
from tkinter import messagebox, ttk, filedialog
import serial
import serial.tools.list_ports
import threading
import time
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec
import os
import csv
import math
import textwrap
from datetime import datetime
import sys
# We wrap the import in try/except so the app doesn't crash if esptool is missing
try:
    import esptool
    HAS_ESPTOOL = True
except ImportError:
    HAS_ESPTOOL = False
import subprocess
# --- FORCED IMPORTS FOR FULLY PORTABLE BINARY ---
import matplotlib
import matplotlib.backends.backend_pdf
import matplotlib.backends.backend_tkagg
import scipy.signal._savitzky_golay  
import numpy as np

try:
    from scipy.signal import savgol_filter
    HAS_SCIPY = True
except ImportError:
    HAS_SCIPY = False

class DynoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Pit Row Dyno Desktop Suite")
        self.root.geometry("620x920") 
        self.root.configure(bg="#2c3e50")
        
        # --- VARIABLES ---
        self.peak_data = {}
        self.comp_data = None
        self.comp_name = ""
        self.is_recording = False
        self.ser = None
        self.save_path = os.getcwd() 
        self.auto_scale = tk.BooleanVar(value=True)

        style = ttk.Style()
        style.theme_use('clam')
        
        header = tk.Frame(root, bg="#34495e", height=60)
        header.pack(fill="x")
        tk.Label(header, text="PIT ROW DYNO CONTROL CENTER", bg="#34495e", fg="white", 
                 font=('Arial', 14, 'bold')).pack(pady=15)

        # --- DYNAMIC SCROLLBAR CONTAINER ---
        self.container = tk.Frame(root, bg="#2c3e50")
        self.container.pack(fill="both", expand=True)
        
        self.canvas = tk.Canvas(self.container, bg="#2c3e50", highlightthickness=0)
        self.scrollbar = ttk.Scrollbar(self.container, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=self.scrollbar.set)
        
        # We don't pack the scrollbar here; the _on_frame_configure method will handle it
        self.canvas.pack(side="left", fill="both", expand=True)
        
        self.content = tk.Frame(self.canvas, bg="#2c3e50", padx=20, pady=5)
        self.canvas_window = self.canvas.create_window((0, 0), window=self.content, anchor="nw")

        self.content.bind("<Configure>", self._on_frame_configure)
        self.canvas.bind("<Configure>", self._on_canvas_configure)

        # LIVE DASHBOARD
        dash_card = tk.LabelFrame(self.content, text=" LIVE PEAK PERFORMANCE ", bg="#1a252f", fg="#3498db", font=('Arial', 10, 'bold'), padx=10, pady=10)
        dash_card.pack(fill="x", pady=(0, 10))
        self.live_hp_label = tk.Label(dash_card, text="0.00 HP", bg="#1a252f", fg="#00f2ff", font=('Arial', 28, 'bold'))
        self.live_hp_label.pack(side="left", expand=True)
        tk.Frame(dash_card, width=2, bg="#34495e").pack(side="left", fill="y", padx=15)
        self.live_tq_label = tk.Label(dash_card, text="0.00 TQ", bg="#1a252f", fg="#ff4d4d", font=('Arial', 28, 'bold'))
        self.live_tq_label.pack(side="left", expand=True)

        # RUN DETAILS
        config_card = tk.LabelFrame(self.content, text=" RUN DETAILS ", bg="#2c3e50", fg="#bdc3c7", font=('Arial', 9, 'bold'), padx=15, pady=10)
        config_card.pack(fill="x", pady=5)
        tk.Label(config_card, text="SESSION IDENTIFIER:", bg="#2c3e50", fg="#bdc3c7").pack(anchor="w")
        self.name_entry = tk.Entry(config_card, font=('Arial', 11), bg="#ecf0f1", relief="flat")
        self.name_entry.insert(0, f"Run_{datetime.now().strftime('%H%M')}")
        self.name_entry.pack(fill="x", pady=(2, 8))
        tk.Label(config_card, text="CONFIGURATION NOTES:", bg="#2c3e50", fg="#bdc3c7").pack(anchor="w")
        self.notes_text = tk.Text(config_card, height=2, font=('Arial', 10), bg="#ecf0f1", relief="flat")
        self.notes_text.pack(fill="x", pady=2)

        # ENVIRONMENT & SETTINGS
        env_card = tk.LabelFrame(self.content, text=" AMBIENT CORRECTION & GRAPH SETTINGS ", bg="#2c3e50", fg="#3498db", font=('Arial', 9, 'bold'), padx=15, pady=10)
        env_card.pack(fill="x", pady=5)
        
        w_row = tk.Frame(env_card, bg="#2c3e50")
        w_row.pack(fill="x")
        tk.Label(w_row, text="Temp °F:", bg="#2c3e50", fg="white").pack(side="left")
        self.temp_in = tk.Entry(w_row, width=4); self.temp_in.insert(0, "77"); self.temp_in.pack(side="left", padx=(5, 10))
        tk.Label(w_row, text="Press inHg:", bg="#2c3e50", fg="white").pack(side="left")
        self.press_in = tk.Entry(w_row, width=5); self.press_in.insert(0, "29.92"); self.press_in.pack(side="left", padx=(5, 10))
        tk.Label(w_row, text="Hum %:", bg="#2c3e50", fg="white").pack(side="left")
        self.hum_in = tk.Entry(w_row, width=4); self.hum_in.insert(0, "40"); self.hum_in.pack(side="left")
        
        tk.Frame(env_card, height=1, bg="#34495e").pack(fill="x", pady=10)

        # SMOOTHING SLIDER
        smooth_row = tk.Frame(env_card, bg="#2c3e50")
        smooth_row.pack(fill="x", pady=(0, 5))
        tk.Label(smooth_row, text="GRAPH SMOOTHING:", bg="#2c3e50", fg="white", font=('Arial', 8, 'bold')).pack(side="left")
        self.smooth_slider = tk.Scale(smooth_row, from_=3, to_=51, orient="horizontal", bg="#2c3e50", fg="#3498db", 
                                     highlightthickness=0, troughcolor="#34495e", showvalue=True)
        self.smooth_slider.set(11) 
        self.smooth_slider.pack(side="left", fill="x", expand=True, padx=10)

        s_row = tk.Frame(env_card, bg="#2c3e50")
        s_row.pack(fill="x")
        self.scale_toggle = tk.Checkbutton(s_row, text="AUTO-SCALE", variable=self.auto_scale, bg="#2c3e50", fg="#2ecc71", selectcolor="#34495e", font=('Arial', 9, 'bold'))
        self.scale_toggle.pack(side="left")
        tk.Label(s_row, text="Fixed Limit:", bg="#2c3e50", fg="white").pack(side="left", padx=(15, 5))
        self.fixed_limit_in = tk.Entry(s_row, width=5); self.fixed_limit_in.insert(0, "20.0"); self.fixed_limit_in.pack(side="left")

        # ACTIONS
        conn_frame = tk.Frame(self.content, bg="#2c3e50", pady=5)
        conn_frame.pack(fill="x")
        self.port_combo = ttk.Combobox(conn_frame, values=self.get_ports(), width=12)
        self.port_combo.pack(side="left", padx=(0, 10))
        if self.port_combo['values']: self.port_combo.current(0)
        
        tk.Button(conn_frame, text="📊 COMPARE", command=self.load_comparison, bg="#3498db", fg="white", width=10).pack(side="right")
        tk.Button(conn_frame, text="📁 FOLDER", command=self.choose_folder, bg="#95a5a6", fg="white", width=10).pack(side="right", padx=5)
        tk.Button(conn_frame, text="🔄 RE-GRAPH", command=self.generate_graph, bg="#1abc9c", fg="white", width=10).pack(side="right", padx=5)
        tk.Button(conn_frame, text="⚡ UPDATE", command=self.update_firmware, bg="#8e44ad", fg="white", width=10).pack(side="right", padx=5)

        # CLEAR COMPARISON BUTTON
        self.btn_clear_comp = tk.Button(self.content, text="❌ CLEAR COMPARISON RUN", command=self.clear_comparison, bg="#e74c3c", fg="white", font=('Arial', 9), height=1)
        self.btn_clear_comp.pack(fill="x", pady=(5, 0))

        self.status_label = tk.Label(self.content, text="SYSTEM READY", bg="#34495e", fg="#2ecc71", font=('Arial', 11, 'bold'), pady=5)
        self.status_label.pack(fill="x", pady=5)
        
        self.btn_action = tk.Button(self.content, text="START DYNO SESSION", command=self.toggle_session, bg="#2ecc71", fg="white", font=('Arial', 12, 'bold'), height=1)
        self.btn_action.pack(fill="x", pady=2)
        
        self.btn_pdf = tk.Button(self.content, text="📄 GENERATE OFFICIAL PDF REPORT", command=self.export_pdf_report, bg="#e67e22", fg="white", font=('Arial', 10, 'bold'), height=1, state="disabled")
        self.btn_pdf.pack(fill="x", pady=2)
        
        self.path_label = tk.Label(self.content, text=f"Saving to: {self.save_path}", bg="#2c3e50", fg="#7f8c8d", font=('Arial', 8))
        self.path_label.pack(pady=5)

    def _on_frame_configure(self, event):
        """Update scrollregion and toggle scrollbar visibility."""
        self.canvas.configure(scrollregion=self.canvas.bbox("all"))
        
        # Check if internal content is taller than the visible canvas area
        if self.content.winfo_reqheight() > self.canvas.winfo_height():
            self.scrollbar.pack(side="right", fill="y")
        else:
            self.scrollbar.pack_forget()

    def _on_canvas_configure(self, event):
        """Ensure internal frame matches canvas width and check scrollbar again."""
        self.canvas.itemconfig(self.canvas_window, width=event.width)
        self._on_frame_configure(None)

    def get_ports(self): return [p.device for p in serial.tools.list_ports.comports()]
    
    def choose_folder(self):
        p = filedialog.askdirectory()
        if p: self.save_path = p; self.path_label.config(text=f"Saving to: ...{p[-40:]}")

    def clear_comparison(self):
        self.comp_data = None
        self.comp_name = ""
        messagebox.showinfo("Comparison Cleared", "Reference data removed.")
        self.generate_graph()

    def load_comparison(self):
        f_path = filedialog.askopenfilename(filetypes=[("CSV Files", "*.csv")])
        if f_path:
            try:
                data = {}
                with open(f_path, 'r') as f:
                    lines = f.readlines(); data_started = False
                    for line in lines:
                        if line.startswith("RPM"): data_started = True; continue
                        if not data_started or line.startswith("#"): continue
                        row = line.strip().split(',')
                        if len(row) >= 3:
                            r, t, h = float(row[0]), float(row[1]), float(row[2])
                            rnd_r = int(50 * round(r / 50)); data[rnd_r] = {'t': t, 'h': h}
                self.comp_data = data; self.comp_name = os.path.basename(f_path)
                messagebox.showinfo("Success", f"Loaded: {self.comp_name}")
                self.generate_graph() 
            except Exception as e: messagebox.showerror("Error", f"Load failed: {e}")

    def get_correction_factor(self):
        try:
            T, P = float(self.temp_in.get()), float(self.press_in.get())
            return round((1.18 * ((29.23 / P) * math.sqrt((T + 460) / 537))) - 0.18, 3)
        except: return 1.0

    def toggle_session(self):
        if not self.is_recording: self.start_session()
        else: self.stop_session("Manual Stop")

    def start_session(self):
        port = self.port_combo.get()
        if not port: return
        try:
            self.ser = serial.Serial(port, 115200, timeout=0.1)
            self.is_recording = True
            self.btn_action.config(text="STOP & FINALIZE", bg="#e74c3c")
            self.btn_pdf.config(state="disabled")
            self.status_label.config(text="SYNCING...", fg="#f1c40f")
            self.peak_data = {}
            threading.Thread(target=self.listen_to_serial, daemon=True).start()
            
            def handshake():
                while self.is_recording:
                    if "READY" in self.status_label.cget("text"): break
                    self.ser.write(b's'); time.sleep(0.5)
            threading.Thread(target=handshake, daemon=True).start()
        except Exception as e: messagebox.showerror("Error", str(e))

    def listen_to_serial(self):
        run_name = self.name_entry.get()
        full_filename = os.path.join(self.save_path, f"{run_name}.csv")
        cf = self.get_correction_factor()
        # Clean notes for CSV
        notes = self.notes_text.get("1.0", "end-1c").replace("\n", " | ")
        
        # 1. Create a memory buffer instead of opening the file immediately
        run_buffer = [] 
        
        # Header info to write later
        header = [
            f"# Pit Row Dyno Run Data",
            f"# Date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
            f"# Weather: {self.temp_in.get()}F, {self.press_in.get()}inHg, {self.hum_in.get()}% Hum",
            f"# SAE CF: {cf}",
            f"# Notes: {notes}",
            "RPM,Torque,Horsepower,EGT"
        ]

        curr_max_hp, curr_max_tq = 0.0, 0.0
            
        while self.is_recording:
            try:
                # This line blocks until data arrives, which is good
                line = self.ser.readline().decode('utf-8', errors='ignore').strip()
                
                if not line: continue

                if line.startswith("RPM"): continue
                
                # Handshake logic
                if "READY" in line: 
                     self.root.after(0, lambda: self.status_label.config(text="CONNECTED - READY", fg="#2ecc71"))
                     continue
                
                # Stop signal from ESP32
                if "EOF" in line: 
                    self.root.after(0, lambda: self.stop_session("RUN COMPLETE"))
                    break
                
                parts = line.split(',')
                if len(parts) >= 3:
                    try:
                        r_raw, t_raw, h_raw = parts[0], parts[1], parts[2]
                        egt_raw = parts[3] if len(parts) > 3 else "0.0"
                        
                        # Store RAW strings to buffer immediately (fast!)
                        run_buffer.append(f"{r_raw},{t_raw},{h_raw},{egt_raw}")

                        # --- LIVE DASHBOARD LOGIC (Keep this) ---
                        # We still parse numbers for the UI, but we don't hold up the loop for disk I/O
                        r = int(float(r_raw))
                        t = float(t_raw) * cf
                        h = float(h_raw) * cf
                        
                        # Update Max values for Live Dash
                        if r > 50:
                            # Update peak tracking dictionary for the graph later
                            rnd_r = int(50 * round(r / 50))
                            if rnd_r not in self.peak_data:
                                self.peak_data[rnd_r] = {'t': t, 'h': h}
                            else:
                                # Logic to keep max peaks
                                if t < (self.peak_data[rnd_r]['t'] * 2.0) or self.peak_data[rnd_r]['t'] == 0:
                                    self.peak_data[rnd_r]['t'] = max(self.peak_data[rnd_r]['t'], t)
                                if h < (self.peak_data[rnd_r]['h'] * 2.0) or self.peak_data[rnd_r]['h'] == 0:
                                    self.peak_data[rnd_r]['h'] = max(self.peak_data[rnd_r]['h'], h)
                            
                            if h > curr_max_hp and h < 500: curr_max_hp = h
                            if t > curr_max_tq and t < 500: curr_max_tq = t
                            
                            # Update UI (Cheap operation)
                            self.root.after(0, lambda rpm=rnd_r, mhp=curr_max_hp, mtq=curr_max_tq: 
                                           self.update_live_dash(rpm, mhp, mtq))
                                           
                    except ValueError: continue
            except: break

        # 2. SAVE TO DISK NOW (Loop is done)
        if run_buffer:
            try:
                with open(full_filename, "w") as f:
                    # Write Header
                    for line in header:
                        f.write(line + "\n")
                    # Write Data
                    for line in run_buffer:
                        f.write(line + "\n")
                print(f"Saved {len(run_buffer)} points to {full_filename}")
            except Exception as e:
                print(f"Error saving file: {e}")

    def update_live_dash(self, rpm, mhp, mtq):
        self.status_label.config(text=f"RECORDING: {rpm} RPM")
        self.live_hp_label.config(text=f"{mhp:.2f} HP")
        self.live_tq_label.config(text=f"{mtq:.2f} TQ")

    def stop_session(self, reason):
        self.is_recording = False
        if self.ser: self.ser.write(b'q'); self.ser.close()
        self.btn_action.config(text="START DYNO SESSION", bg="#2ecc71")
        self.btn_pdf.config(state="normal")
        self.status_label.config(text=reason, fg="#3498db")
        self.generate_graph()

    def generate_graph(self):
        if not self.peak_data and not self.comp_data: 
            messagebox.showwarning("No Data", "No data available to graph.")
            return
        plt.close('all') 
        fig = self.render_performance_plot(is_pdf=False)
        fig.canvas.manager.set_window_title(f"Analysis: {self.name_entry.get()}")
        plt.show()

    def render_performance_plot(self, is_pdf=False):
        cf = self.get_correction_factor()
        win_len = int(self.smooth_slider.get())
        if win_len % 2 == 0: win_len += 1
        if win_len <= 3: win_len = 5 # SG Safety Floor

        # Theme Configuration
        if is_pdf:
            plt.style.use('default'); fig = plt.figure(figsize=(8.5, 11))
            p_color, s_color, text_col = '#e74c3c', '#3498db', 'black'
        else:
            plt.style.use('dark_background'); fig = plt.figure(figsize=(12, 7))
            p_color, s_color, text_col = '#ff4d4d', '#00f2ff', 'white'

        gs = GridSpec(4, 1, height_ratios=[0.08, 0.15, 0.52, 0.25], hspace=0.45)
        
        # Determine peaks for Current Run
        p_hp, hp_r, p_tq, tq_r = 0.0, 0, 0.0, 0
        if self.peak_data:
            rpms = sorted(self.peak_data.keys())
            tq_raw = np.array([self.peak_data[r]['t'] for r in rpms])
            hp_raw = np.array([self.peak_data[r]['h'] for r in rpms])
            if HAS_SCIPY and len(rpms) > win_len:
                tq = savgol_filter(tq_raw, window_length=win_len, polyorder=3)
                hp = savgol_filter(hp_raw, window_length=win_len, polyorder=3)
            else:
                tq, hp = tq_raw, hp_raw
            if len(hp) > 0: p_hp = float(max(hp)); hp_r = rpms[np.argmax(hp)]
            if len(tq) > 0: p_tq = float(max(tq)); tq_r = rpms[np.argmax(tq)]

        # Header Section
        ax_h = fig.add_subplot(gs[0]); ax_h.axis('off')
        ax_h.text(0.5, 0.7, "PIT ROW DYNO PERFORMANCE REPORT", fontsize=18, weight='bold', ha='center', color='#3498db')
        ax_h.text(0.5, 0.2, f"Run ID: {self.name_entry.get()} | Date: {datetime.now().strftime('%Y-%m-%d')}", fontsize=10, ha='center', color=text_col)

        # Performance Summary Table
        ax_t = fig.add_subplot(gs[1]); ax_t.axis('off')
        env_ref = f"{self.temp_in.get()}°F / {self.press_in.get()}inHg / {self.hum_in.get()}% Hum"
        table_vals = [['PEAK HORSEPOWER', f"{p_hp:.2f} HP", f"at {hp_r} RPM"],
                      ['PEAK TORQUE', f"{p_tq:.2f} ft-lbs", f"at {tq_r} RPM"],
                      ['SAE CORRECTION', f"{cf}", env_ref]]
        tab = ax_t.table(cellText=table_vals, colLabels=['Metric', 'Result', 'Reference'], loc='center', cellLoc='center')
        tab.auto_set_font_size(False); tab.set_fontsize(10); tab.scale(1, 1.8)
        if not is_pdf:
            for cell in tab._cells:
                tab._cells[cell].set_facecolor('#1a252f'); tab._cells[cell].set_text_props(color='white')

        # Main Graph Section
        ax_g = fig.add_subplot(gs[2]); ax_hp_axis = ax_g.twinx()
        if self.peak_data:
            ax_g.plot(rpms, tq, color=p_color, lw=3, label='Torque')
            ax_hp_axis.plot(rpms, hp, color=s_color, lw=3, label='Horsepower')

        if self.comp_data:
            c_rpms = sorted(self.comp_data.keys())
            c_tq = np.array([self.comp_data[r]['t'] for r in c_rpms])
            c_hp = np.array([self.comp_data[r]['h'] for r in c_rpms])
            if HAS_SCIPY and len(c_rpms) > win_len:
                c_tq = savgol_filter(c_tq, window_length=win_len, polyorder=3)
                c_hp = savgol_filter(c_hp, window_length=win_len, polyorder=3)
            ax_g.plot(c_rpms, c_tq, color=p_color, lw=1.5, ls='--', alpha=0.6, label=f'Ref Torque')
            ax_hp_axis.plot(c_rpms, c_hp, color=s_color, lw=1.5, ls='--', alpha=0.6, label=f'Ref Horsepower')

        # COMBINED LEGEND FIX
        lines_g, labels_g = ax_g.get_legend_handles_labels()
        lines_hp, labels_hp = ax_hp_axis.get_legend_handles_labels()
        ax_g.legend(lines_g + lines_hp, labels_g + labels_hp, loc='upper left', fontsize='small')

        # PEAK INDICATORS
        box_style = dict(boxstyle='round', facecolor='white' if is_pdf else 'black', alpha=0.8, edgecolor='none')
        if p_hp > 0: ax_hp_axis.text(hp_r, p_hp * 1.05, f" {p_hp:.2f} HP ", color=s_color, weight='bold', ha='center', bbox=box_style)
        if p_tq > 0: ax_g.text(tq_r, p_tq * 1.05, f" {p_tq:.2f} TQ ", color=p_color, weight='bold', ha='center', bbox=box_style)

        ax_g.set_xlabel('Engine RPM', weight='bold')
        ax_g.set_ylabel('Torque (ft-lbs)', color=p_color, weight='bold')
        ax_hp_axis.set_ylabel('Horsepower (HP)', color=s_color, weight='bold')
        ax_g.grid(True, alpha=0.1)
        
        # Scaling
        if self.auto_scale.get():
            all_vals = []
            if self.peak_data: all_vals += list(tq) + list(hp)
            if self.comp_data: all_vals += list(c_tq) + list(c_hp)
            s_max = (max(all_vals) * 1.2) if all_vals else 20.0
        else:
            try: s_max = float(self.fixed_limit_in.get())
            except: s_max = 20.0
        ax_g.set_ylim(0, s_max); ax_hp_axis.set_ylim(0, s_max)

        # Notes
        ax_n = fig.add_subplot(gs[3]); ax_n.axis('off')
        wrapped = textwrap.fill(f"NOTES: {self.notes_text.get('1.0', 'end-1c')}", width=85)
        ax_n.text(0, 0.8, wrapped, fontsize=10, va='top', family='monospace', color=text_col)

        return fig

    def export_pdf_report(self):
        try:
            pdf_path = os.path.join(self.save_path, f"{self.name_entry.get()}_Report.pdf")
            fig = self.render_performance_plot(is_pdf=True)
            plt.savefig(pdf_path, dpi=300, bbox_inches='tight'); plt.close()
            messagebox.showinfo("Success", f"Report Saved: {pdf_path}")
        except Exception as e: messagebox.showerror("Export Error", str(e))

    def update_firmware(self):
        # 1. Select the file
        firmware_path = filedialog.askopenfilename(
           title="Select Firmware File",
            filetypes=[("Binary Files", "*.bin"), ("All Files", "*.*")]
        )
        if not firmware_path:
            return

        # 2. Confirm
        if not messagebox.askyesno("Confirm Update", "Ready to flash firmware?\n\nDo not unplug power!"):
            return

        # 3. DISCONNECT SERIAL
        if self.ser and self.ser.is_open:
            self.stop_session("Updating Firmware...") 
            self.ser.close()
    
        port = self.port_combo.get()
        
        # --- NEW CODE FOR PORTABILITY ---
        # Do not use "esptool.py" as a command string. 
        # Pass the arguments directly to the library's main function.
        esptool_args = [
            "--port", port,
            "--baud", "460800",
            "--before", "default_reset",
            "--after", "hard_reset",
            "write_flash",
            "-z",
            "0x10000",
            firmware_path
        ]

        self.status_label.config(text="FLASHING... PLEASE WAIT...", fg="#e74c3c")
        self.root.update()

        try:
            # CALL INTERNAL FUNCTION INSTEAD OF SUBPROCESS
            # We redirect stdout/stderr to suppress console spam if needed, 
            # or you can let it print to the terminal if you launched it there.
            import esptool
            esptool.main(esptool_args)
        
            messagebox.showinfo("Success", "Firmware Updated Successfully!")
            self.status_label.config(text="UPDATE COMPLETE", fg="#2ecc71")

        except Exception as e:
            # esptool.main() raises an exception on failure
            messagebox.showerror("Update Failed", f"The flashing process failed.\nError: {e}")
            self.status_label.config(text="UPDATE FAILED", fg="red")

if __name__ == "__main__":
    try:
        from ctypes import windll
        windll.shcore.SetProcessDpiAwareness(1)
    except: pass
    root = tk.Tk(); app = DynoApp(root); root.mainloop()