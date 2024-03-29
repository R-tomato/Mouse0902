/*
 * drive.c
 *
 *  Created on: May 2, 2019
 *      Author: blue
 */


#include "global.h"


/*==========================================================
    走行系 上位関数
==========================================================*/
/*
    マウスフラグ(MF)
      6Bit:デフォルトインターバルフラグ
      5Bit:減速フラグ
      4Bit:加速フラグ
      3Bit:制御フラグ
      1Bit:二次走行フラグ
*/
//+++++++++++++++++++++++++++++++++++++++++++++++
//half_sectionA
// 半区画分加速しながら走行する
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void half_sectionA(void){

  MF.FLAG.CTRL = 1;                   //制御を有効にする
  driveA(PULSE_SEC_HALF);             //半区画のパルス分加速しながら走行。走行後は停止しない
  get_wall_info();                    //壁情報を取得，片壁制御の有効・無効の判断
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//half_sectionD
// 半区画分減速しながら走行し停止する
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void half_sectionD(void){

  MF.FLAG.CTRL = 1;                   //制御を有効にする
  driveD(PULSE_SEC_HALF);             //半区画のパルス分減速しながら走行。走行後は停止する
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//one_section
// 1区画分進んで停止する。1区画走行用
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void one_section(void){

  half_sectionA();                    //半区画分加速しながら走行する
  half_sectionD();                    //半区画分減速しながら走行し停止
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//one_sectionU
// 等速で1区画分進む
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void one_sectionU(void){

  MF.FLAG.CTRL = 1;                   //制御を有効にする
  driveU(PULSE_SEC_HALF);             //半区画のパルス分等速走行。走行後は停止しない
  driveU(PULSE_SEC_HALF);             //半区画のパルス分等速走行。走行後は停止しない
  get_wall_info();                    //壁情報を取得
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//rotate_R90
// turn reft 90
// a引数：なし
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void rotate_R90(void){

  MF.FLAG.CTRL = 0;                   //制御無効
  drive_set_dir(ROTATE_R);            //右に旋回するようモータの回転方向を設定
  drive_wait();                       //機体が安定するまで待機
  drive_wait();
  driveC(PULSE_ROT_R90);              //デフォルトインターバルで指定パルス分回転。回転後に停止する
  drive_wait();                       //機体が安定するまで待機
  drive_set_dir(FORWARD);             //前進するようにモータの回転方向を設定
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//rotate_L90
// turn light 90
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void rotate_L90(void){

  MF.FLAG.CTRL = 0;                   //制御を無効にする
  drive_set_dir(ROTATE_L);            //左に旋回するようモータの回転方向を設定
  drive_wait();                       //機体が安定するまで待機
  drive_wait();
  driveC(PULSE_ROT_L90);              //デフォルトインターバルで指定パルス分回転。回転後に停止する
  drive_wait();                       //機体が安定するまで待機
  drive_set_dir(FORWARD);             //前進するようにモータの回転方向を設定
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//rotate_180
// turn 180
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void rotate_180(void){

  MF.FLAG.CTRL = 0;                   // 制御を無効にする
  drive_set_dir(ROTATE_R);            // 左に旋回するようモータの回転方向を設定
  drive_wait();                       // 機体が安定するまで待機
  driveC(PULSE_ROT_180);              // デフォルトインターバルで指定パルス分回転。回転後に停止する
  drive_wait();                       // 機体が安定するまで待機
  drive_set_dir(FORWARD);             // 前進するようにモータの回転方向を設定
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//re_set_position(追加
//a尻当て
//a引数:なし
//a返り値:なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void reset_position(void){

  MF.FLAG.CTRL = 0;

  drive_set_dir(ROTATE_R);    //turn Right
  drive_wait();
  driveC(PULSE_ROT_R90);
  drive_wait();

  drive_set_dir(BACK);        //back
  drive_wait();
  driveC(PULSE_SETPOS_BACK);
  drive_wait();

  drive_set_dir(FORWARD);     //forward
  drive_wait();
  driveC(PULSE_SETPOS_SET);
  drive_wait();

  drive_set_dir(ROTATE_L);    //Left
  drive_wait();
  driveC(PULSE_ROT_L90);
  drive_wait();

  drive_set_dir(BACK);        //back
  drive_wait();
  driveC(PULSE_SETPOS_BACK);
  drive_wait();

  drive_set_dir(FORWARD);     //forward
  drive_wait();
  driveC(PULSE_SETPOS_SET);
  drive_wait();

}

//+++++++++++++++++++++++++++++++++++++++++++++++
//only_set_position
//機体の尻を壁に充てるだけの関数
//引数:なし
//戻り値なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void only_set_position(void){

  MF.FLAG.CTRL = 0;                   //制御を無効にする
  drive_set_dir(BACK);                //後退するようモータの回転方向を設定
  drive_wait();                       //機体が安定するまで待機
  driveC(PULSE_SETPOS_BACK);          //尻を当てる程度に後退。回転後に停止する
  drive_wait();                       //機体が安定するまで待機
  drive_set_dir(FORWARD);
  drive_wait();
  driveC(PULSE_SETPOS_SET);
  drive_wait();

}

//+++++++++++++++++++++++++++++++++++++++++++++++
//set_position
// 機体の尻を壁に当てて場所を区画中央に合わせる
// 引数：sw …… 0以外ならget_base()する
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void set_position(uint8_t sw){

  MF.FLAG.CTRL = 0;                   //制御を無効にする
  drive_set_dir(BACK);                //後退するようモータの回転方向を設定
  drive_wait();                       //機体が安定するまで待機
  driveC(PULSE_SETPOS_BACK);          //尻を当てる程度に後退。回転後に停止する
  drive_wait();                       //機体が安定するまで待機
  if(sw){
    get_base();
  }
  drive_set_dir(FORWARD);             //前進するようにモータの回転方向を設定
  drive_wait();                       //機体が安定するまで待機
  driveC(PULSE_SETPOS_SET);           //デフォルトインターバルで指定パルス分回転。回転後に停止する
  drive_wait();                       //機体が安定するまで待機
}



/*==========================================================
    走行系 基幹関数
==========================================================*/
/*
    基本仕様として，基幹関数は，
    引数1：dist …… 走行パルス数
*/
//+++++++++++++++++++++++++++++++++++++++++++++++
//driveA
// 指定パルス分加速走行する
// 引数1：dist …… 走行するパルス
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void driveA(uint16_t dist){

  //====a走行====
  //----a走行開始----
  MF.FLAG.DECL = 0;
  MF.FLAG.DEF = 0;
  MF.FLAG.ACCL = 1;                   //a減速・デフォルトインターバルフラグをクリア，加速フラグをセット
  drive_reset_t_cnt();                //aテーブルカウンタをリセット
  drive_start();                      //a走行開始

  //----a走行----
  while((pulse_l < dist) || (pulse_r < dist));      //a左右のモータが指定パルス以上進むまで待機

  drive_stop();
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//driveD
// a指定パルス分減速走行して停止する
// a引数1：dist …… 走行するパルス
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void driveD(uint16_t dist){

  //====走行====
  //----走行開始----
  MF.FLAG.DECL = 0;
  MF.FLAG.DEF = 0;
  MF.FLAG.ACCL = 0;                   //加速・減速・デフォルトインターバルフラグをクリア
  drive_start();                      //痩躯開始

  int16_t c_pulse = dist - (t_cnt_l - min_t_cnt);     //等速走行距離 = 総距離 - 減速に必要な距離
  if(c_pulse > 0){
    //----等速走行----
    while((pulse_l < c_pulse) || (pulse_r < c_pulse));  //左右のモータが等速分のパルス以上進むまで待機
  }

  //----減速走行----
  MF.FLAG.DECL = 1;                   //減速フラグをセット
  while((pulse_l < dist) || (pulse_r < dist));      //左右のモータが減速分のパルス以上進むまで待機

  //====走行終了====
  drive_stop();
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//driveU
// 指定パルス分等速走行して停止する
//引数1：dist …… 走行するパルス
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void driveU(uint16_t dist){

  //====等速走行開始====
  MF.FLAG.DECL = 0;
  MF.FLAG.DEF = 0;
  MF.FLAG.ACCL = 0;                   //加速・減速・デフォルトインターバルフラグをクリア
  drive_start();                      //走行開始

  //====走行====
  while((pulse_l < dist) || (pulse_r < dist));      //左右のモータが減速分のパルス以上進むまで待機

  //====走行終了====
  drive_stop();
}

//+++++++++++++++++++++++++++++++++++++++++++++++
//driveC
// a指定パルス分デフォルトインターバルで走行して停止する
// a引数1：dist …… 走行するパルス
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void driveC(uint16_t dist){

  //====a回転開始====
  MF.FLAG.DECL = 0;
  MF.FLAG.DEF = 1;
  MF.FLAG.ACCL = 0;                   //a加速・減速フラグをクリア，デフォルトインターバルフラグをセット
  drive_start();                      //a走行開始

  //====a回転====
  while((pulse_l < dist) || (pulse_r < dist));      //a左右のモータが定速分のパルス以上進むまで待機

  drive_stop();
}




/*==========================================================
    初期化関数・設定関数・その他関数
==========================================================*/
//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_init
// a走行系の変数の初期化，モータードライバ関係のGPIO設定とPWM出力に使うタイマの設定をする
// a引数：なし
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_init(void){

  //====a走行系の変数の初期化====
  max_t_cnt = MAX_T_CNT;      //aテーブルカウンタ最高値初期化     MAX_T_CNTはparams.hにマクロ定義あり
  min_t_cnt = MIN_T_CNT;      //aテーブルカウンタ最低値初期化     MIN_T_CNTはparams.hにマクロ定義あり

  //====aマウスフラグの初期化===
  MF.FLAGS = 0;         //aフラグクリア


  //====aステッピングモータの初期化====
  drive_disable_motor();       //aステッピングモータ励磁OFF
  drive_set_dir(FORWARD);     //a前進するようにモータの回転方向を設定


  //====PWM出力に使うタイマの設定====
  __HAL_TIM_SET_AUTORELOAD(&htim16, DEFAULT_INTERVAL);
  __HAL_TIM_SET_AUTORELOAD(&htim17, DEFAULT_INTERVAL);


}


//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_enable_motor
// aステッピングモータを励磁する
// a引数：なし
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_enable_motor(void){
  HAL_GPIO_WritePin(M3_GPIO_Port, M3_Pin, GPIO_PIN_RESET);  //aステッピングモーター励磁ON
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_disable_motor
// aステッピングモータの励磁を切る
// a引数：なし
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_disable_motor(void){
  HAL_GPIO_WritePin(M3_GPIO_Port, M3_Pin, GPIO_PIN_SET);    //aステッピングモーター励磁OFF
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_reset_t_cnt
// aテーブルカウンタをリセット（min_t_cntの値にセット）する
// a引数：なし
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_reset_t_cnt(void){
  t_cnt_l = t_cnt_r = min_t_cnt;
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_start
// a走行を開始する
// a（pulse_l,pulse_rを0にリセットしてタイマを有効にする）
// a引数：なし
// a戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_start(void){

  pulse_l = pulse_r = 0;      //a走行したパルス数の初期化

  //====PWM出力に使うタイマを有効にする====
  /*--------------------------------------------------------------------
    TIM16 : a16ビットタイマ。左モータの制御に使う。出力はTIM16_CH1
  --------------------------------------------------------------------*/
  __HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
  __HAL_TIM_ENABLE_IT(&htim16, TIM_IT_UPDATE);
  HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);

  /*--------------------------------------------------------------------
    TIM17 : a16ビットタイマ。右モータの制御に使う。出力はTIM17_CH1
  --------------------------------------------------------------------*/
  __HAL_TIM_CLEAR_FLAG(&htim17, TIM_FLAG_UPDATE);
  __HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);
  HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);

}


//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_stop
// 走行を終了する
// （タイマを止めてタイマカウント値を0にリセットする）
// 引数1：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_stop(void){

  //====PWM出力に使うタイマを停止させる====
  /*--------------------------------------------------------------------
    TIM16 : 16ビットタイマ。左モータの制御に使う。出力はTIM16_CH1
  --------------------------------------------------------------------*/
  HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);

  /*--------------------------------------------------------------------
    TIM17 : 16ビットタイマ。右モータの制御に使う。出力はTIM17_CH1
  --------------------------------------------------------------------*/
  HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);

  __HAL_TIM_SET_COUNTER(&htim16, 0);  // Reset Counter
  __HAL_TIM_SET_COUNTER(&htim17, 0);  // Reset Counter
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//drive_set_dir
// 進行方向を設定する
// 引数1：d_dir …… どの方向に進行するか  0桁目で左，1桁目で右の方向設定
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void drive_set_dir(uint8_t d_dir){

  //====左モータ====
  switch(d_dir & 0x0f){     //0~3ビット目を取り出す
    //----正回転----
    case 0x00:                      //0x00の場合
      HAL_GPIO_WritePin(CW_CCW_L_GPIO_Port, CW_CCW_L_Pin, MT_FWD_L);  //左を前進方向に設定
      break;
    //----逆回転----
    case 0x01:                      //0x01の場合
      HAL_GPIO_WritePin(CW_CCW_L_GPIO_Port, CW_CCW_L_Pin, MT_BACK_L); //左を後進方向に設定
      break;
  }
  //====右モータ====
  switch(d_dir & 0xf0){     //4~7ビット目を取り出す
    case 0x00:                      //0x00の場合
      HAL_GPIO_WritePin(CW_CCW_R_GPIO_Port, CW_CCW_R_Pin, MT_FWD_R);  //右を前進方向に設定
      break;
    case 0x10:                      //0x10の場合
      HAL_GPIO_WritePin(CW_CCW_R_GPIO_Port, CW_CCW_R_Pin, MT_BACK_R); //右を後進方向に設定
      break;
  }
}


//+++++++++++++++++++++++++++++++++++++++++++++++
//test_run
// test run mode
// 引数：なし
// 戻り値：なし
//+++++++++++++++++++++++++++++++++++++++++++++++
void test_run(void){

  int mode = 0;
  drive_enable_motor();

  while(1){

    mode = select_mode(mode);

    int i;
    switch(mode){

      case 0:
        //----尻当て----
        printf("Set Position.\n");
        set_position(0);
        break;
      case 1:
        //----6区画等速走行----
        printf("6 Section, Forward, Constant Speed.\n");
        MF.FLAG.CTRL = 0;           // 制御を無効にする
        drive_set_dir(FORWARD);     // 前進するようにモータの回転方向を設定
        for(i = 0; i < 6; i++){
          driveC(PULSE_SEC_HALF*2); // 一区画のパルス分デフォルトインターバルで走行
          drive_wait();             //wait until stable
        }
        break;
      case 2:
        //----Right turn 90----
        printf("Rotate R90.\n");
        for(i = 0; i < 16; i++){
          rotate_R90();
        }
        break;
      case 3:
        //----Left turn 90----
        printf("Rotate L90.\n");
        for(i = 0; i < 16; i++){
          rotate_L90();
        }
        break;
      case 4:
        //----turn 180----
        printf("Rotate 180.\n");
        for(i = 0; i < 8; i++){
          rotate_180();
        }
        break;
      case 5:
        //----尻当て----

        MF.FLAG.SCND = 0;

        reset_position();

        break;
      case 6:
        break;
      case 7:
        //----6区画連続走行----
        printf("6 Section, Forward, Continuous.\n");
        MF.FLAG.CTRL = 0;           // 制御を無効にする
        drive_set_dir(FORWARD);     // 前進するようにモータの回転方向を設定
        driveA(PULSE_SEC_HALF);     // 半区画のパルス分加速しながら走行
        for(i = 0; i < 6-1; i++){
          driveU(PULSE_SEC_HALF*2); // 一区画のパルス分等速走行
        }
        driveD(PULSE_SEC_HALF);     //半区画のパルス分減速しながら走行。走行後は停止する
        break;
    }

  }
  drive_disable_motor();
}
