#ifndef _qt602240_h_
#define _qt602240_h_

#define GPIO_VDD_TP_EN              0
#define GPIO_TP_SIGNAL_EN           89
//#define GPIO_TP_RST_N               91
//#define GPIO_TP_INT_N               92
#define GPIO_TP_RST_N               23
#define GPIO_TP_INT_N               89
#define DEFAULT_REG_NUM             64

#define MSB(uint16_t)  (((uint8_t* )&uint16_t)[1])
#define LSB(uint16_t)  (((uint8_t* )&uint16_t)[0])

#define TOUCH_DEVICE_NAME           "qt602240"	// Device Name
#define TOUCH_DEVICE_VREG           "wlan"
#define TOUCH_DEVICE_I2C_ADDRESS    0x4Bu

#define LOW                         0
#define HIGH                        1
#define FALSE                       0
#define TRUE                        1

#define TS_MAX_POINTS               2
#define TS_MAX_X                    1023
#define TS_MIN_X                    0
#if defined(CONFIG_FIH_PROJECT_SA4I3)
#define TS_MAX_Y                    1023
#else
//#define TS_MAX_Y                    975
#define TS_MAX_Y                    850
#endif
#define TS_MIN_Y                    0

//#define TS_MAX_KEYS                 4
//#define TS_KEY1_X                   200
//#define TS_KEY2_X                   512
//#define TS_KEY3_X                   850
//#define TS_KEY4_X                   1024
#define TS_MAX_KEYS                 3
#define TS_KEY1_X                   340
#define TS_KEY2_X                   680
#define TS_KEY3_X                   1024



#define DB_LEVEL1                   1
#define DB_LEVEL2                   2
#define TCH_DBG(level, message, ...) \
    do { \
        if ((level) <= qt_debug_level) \
            printk("[TOUCH] %s : " message "\n", __FUNCTION__, ## __VA_ARGS__); \
    } while (0)
#define TCH_ERR(msg, ...) printk("[TOUCH_ERR] %s : " msg "\n", __FUNCTION__, ## __VA_ARGS__)
#define TCH_MSG(msg, ...) printk("[TOUCH] " msg "\n", ## __VA_ARGS__)
#define hwid fih_read_orig_hwid_from_smem()

struct point_info{
    int x;
    int y;
    int num;
    int first_area;
    int last_area;
};

struct dynamic_info{
    int HW_ID;
    int KEYCODE[TS_MAX_KEYS];
};

struct qt602240_info {
    struct i2c_client *client;
    struct input_dev  *touch_input;
    struct input_dev  *keyevent_input;
    struct work_struct wqueue;
    struct point_info points[TS_MAX_POINTS];
    struct dynamic_info dynamic;
#ifdef CONFIG_HAS_EARLYSUSPEND
    struct early_suspend es;
#endif
    int irq;
    bool early_suspend_state;
    bool suspend_state;
    int first_finger_id;
    bool facedetect;
    uint8_t T7[3];
} *qt602240;

enum ts_state {
    NO_TOUCH = 0,
    PRESS_TOUCH_AREA,
    PRESS_KEY1_AREA,
    PRESS_KEY2_AREA,
    PRESS_KEY3_AREA,
    PRESS_KEY4_AREA
};

/* FIH, Henry Juang, 2009/11/20 ++*/
/* [FXX_CR], Add for proximity driver to turn on/off BL and TP. */
int notify_from_proximity_ai1(bool bFlag);  //Added for test
/* FIH, Henry Juang, 2009/11/20 --*/
#endif
