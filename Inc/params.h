/*
 * params.h
 *
 *  Created on: May 2, 2019
 *      Author: blue
 */

#ifndef INC_PARAMS_H_
#define INC_PARAMS_H_



/*============================================================
    各種定数（パラメータ）設定
============================================================*/
/*------------------------------------------------------------
    走行系
------------------------------------------------------------*/
//----走行パルス関連----
#define PULSE_SEC_HALF      200  // 半区画走行用パルス。2倍すると1区画分に 208(202に変更
#define PULSE_ROT_R90       161  // 右90度回転用パルス数 145(158　に変更
#define PULSE_ROT_L90       161   // 左90度回転用パルス数 145(158　に変更
#define PULSE_ROT_180       322   // 180 度回転用パルス数 289
#define PULSE_SETPOS_BACK   300   // 後ろ壁に当てるために下がるパルス数
#define PULSE_SETPOS_SET    70    // 後ろ壁から中央までのパルス数
//----テーブルカウンタ関連----
#define MAX_T_CNT PULSE_SEC_HALF  // テーブルカウンタの最大値
#define MIN_T_CNT 0               //テーブルカウンタの最小値
//----タイマ関連----
#define DEFAULT_INTERVAL  3000    //デフォルトのインターバル


//----動作方向関連----
#define MT_FWD_L  GPIO_PIN_RESET    //CW/CCWで前に進む出力（左）
#define MT_BACK_L GPIO_PIN_SET      //CW/CCWで後ろに進む出力（左）
#define MT_FWD_R  GPIO_PIN_SET      //CW/CCWで前に進む出力（右）
#define MT_BACK_R GPIO_PIN_RESET    //CW/CCWで後ろに進む出力（右）



/*------------------------------------------------------------
    センサ系
------------------------------------------------------------*/
//---Wall Sensor(value)----
#define WALL_BASE_FR  150    //Front Right Sensor
#define WALL_BASE_FL  150    //Front Left Sensor
#define WALL_BASE_R   600   //Right Sensor
#define WALL_BASE_L   400   //Left Sensor

//----CTRL BASE----
#define CTRL_BASE_L     200   //Left
#define CTRL_BASE_R     300  //Right
#define CTRL_MAX        4000  //Max
#define CTRL_CONT_HIGH  0.08F  //　両壁がある場合の制御
#define CTRL_CONT_LOW   0.0001F  //　片方壁がある時の制御
#define CHANGE_CONT_R   300
#define CHANGE_CONT_L   400

//----赤外線（赤色）LED発光待機時間（単位はマイクロ秒）
#define IR_WAIT_US  15



/*------------------------------------------------------------
    探索系
------------------------------------------------------------*/
//----Goal ccordinate----
#define GOAL_X 9  //7
#define GOAL_Y 6  //7


#endif /* INC_PARAMS_H_ */
