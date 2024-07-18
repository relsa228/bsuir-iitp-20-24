package com.example.quarter_pounder.services.converters;

import com.example.quarter_pounder.models.WeightModel;

class WeightConverter {
    private val weightModel: WeightModel = WeightModel();

    //Killograms***************************
    fun killogrammsToTonnes(kilogrammOrTonne: Double, option: Boolean): Double {
        if(option)
            return kilogrammOrTonne * weightModel.kilogrammsToTonne;
        return kilogrammOrTonne / weightModel.kilogrammsToTonne;
    }

    fun killogrammsToLb(killogramOrLb: Double, option: Boolean): Double {
        if(option)
            return killogramOrLb * weightModel.kilogrammsToLb;
        return killogramOrLb / weightModel.kilogrammsToLb;
    }

    fun killogrammsToOunce(killogramOrOunce: Double, option: Boolean): Double {
        if(option)
            return killogramOrOunce * weightModel.kilogrammsToOunce;
        return killogramOrOunce / weightModel.kilogrammsToOunce;
    }

    //Tonne***************************
    fun tonneToLb(tonneOrLb: Double, option: Boolean): Double {
        if(option)
            return tonneOrLb * weightModel.tonneToLb;
        return tonneOrLb / weightModel.tonneToLb;
    }

    fun tonneToOunce(tonneOrOunce: Double, option: Boolean): Double {
        if(option)
            return tonneOrOunce * weightModel.tonneToOunce;
        return tonneOrOunce / weightModel.tonneToOunce;
    }

    //Lb***************************
    fun lbToOunce(lbOROunce: Double, option: Boolean): Double {
        if(option)
            return lbOROunce * weightModel.lbToOunce;
        return lbOROunce / weightModel.lbToOunce;
    }
}
