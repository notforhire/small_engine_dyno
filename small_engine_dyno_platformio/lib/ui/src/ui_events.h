#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void calibrateLow(lv_event_t * e);
void calibrateHigh(lv_event_t * e);
void startDyno(lv_event_t * e);
void gaugeSelect(lv_event_t * e);
void drawChart(lv_event_t * e);
void resetMax(lv_event_t * e);
void rpmRangeSelect(lv_event_t * e);
void firstTorqueRange(lv_event_t * e);
void secondTorqueRange(lv_event_t * e);
void thirdTorqueRange(lv_event_t * e);
void fourthTorqueRange(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
