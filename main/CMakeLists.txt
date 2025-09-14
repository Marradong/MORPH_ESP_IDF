set(srcs
        "main.c"
        "sketch.cpp"
        "batterymonitor.cpp"
        "controller.cpp"
        "imu.cpp"
        "leg.cpp"
        "servodriver.cpp")

set(requires "bluepad32" "bluepad32_arduino" "arduino" "btstack")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "."
                    REQUIRES "${requires}")
