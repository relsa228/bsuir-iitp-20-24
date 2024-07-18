package com.example.quarter_pounder.models

class DistanceModel {
    val meterToIn: Double;
    val meterToFt: Double;
    val meterToYd: Double;
    val meterToMi: Double;

    val inToFt: Double;
    val inToYd: Double;
    val inToMi: Double;

    val ftToYd: Double;
    val ftToMi: Double;

    val miToYd: Double;

    init {
        meterToIn = 39.3700787402;
        meterToFt = 3.280839895;
        meterToYd = 1.0936132983;
        meterToMi = 0.0006213712;

        inToFt = 0.0833333333;
        inToYd = 0.0277777778;
        inToMi = 0.0000157828;

        ftToYd = 0.3333333333;
        ftToMi = 0.0001893939;

        miToYd = 1760.0;
    }
}