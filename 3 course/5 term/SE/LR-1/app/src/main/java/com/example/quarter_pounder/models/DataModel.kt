package com.example.quarter_pounder.models

class DataModel() {
    val bitsToBytes: Double;
    val bitsToKilobytes: Double;
    val bitsToMegabytes: Double;

    val bytesToKilobytes: Double;
    val bytesToMegabytes: Double;

    val kilobytesToMegabytes: Double;

    init {
        bitsToBytes = 0.125;
        bitsToKilobytes = 0.0001220703;
        bitsToMegabytes = 0.00000011921;

        bytesToKilobytes = 0.0009765625;
        bytesToMegabytes = 0.00000095367;

        kilobytesToMegabytes = 0.0;
    }
}