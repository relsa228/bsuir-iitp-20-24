package com.example.quarter_pounder.models

class WeightModel {
    val kilogrammsToTonne: Double;
    val kilogrammsToOunce: Double;
    val kilogrammsToLb: Double;

    val tonneToOunce: Double;
    val tonneToLb: Double;

    val lbToOunce: Double;

    init {
        kilogrammsToTonne = 0.001;
        kilogrammsToOunce = 35.2739619496;
        kilogrammsToLb = 2.2046226218;

        tonneToOunce = 35273.96194958;
        tonneToLb = 2204.6226218488;

        lbToOunce = 16.0;
    }

}