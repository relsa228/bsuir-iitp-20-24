package com.example.quarter_pounder.services.converters

import com.example.quarter_pounder.models.DistanceModel

class DistanceConverter {
    private val distanceModel: DistanceModel = DistanceModel();

    //Meter***************************
    fun meterToIn(meterOrIn: Double, option: Boolean): Double {
        if(option)
            return meterOrIn * distanceModel.meterToIn;
        return meterOrIn / distanceModel.meterToIn;
    }

    fun meterToFt(meterOrFt: Double, option: Boolean): Double {
        if(option)
            return meterOrFt * distanceModel.meterToFt;
        return meterOrFt / distanceModel.meterToFt;
    }

    fun meterToMi(meterOrMi: Double, option: Boolean): Double {
        if(option)
            return meterOrMi * distanceModel.meterToMi;
        return meterOrMi / distanceModel.meterToMi;
    }

    fun meterToYd(meterOrYd: Double, option: Boolean): Double {
        if(option)
            return meterOrYd * distanceModel.meterToYd;
        return meterOrYd / distanceModel.meterToYd;
    }

    //In***************************
    fun inToFt(inOrFt: Double, option: Boolean): Double {
        if(option)
            return inOrFt * distanceModel.inToFt;
        return inOrFt / distanceModel.inToFt;
    }

    fun inToYd(inOrYd: Double, option: Boolean): Double {
        if(option)
            return inOrYd * distanceModel.inToYd;
        return inOrYd / distanceModel.inToYd;
    }

    fun inToMi(inOrMi: Double, option: Boolean): Double {
        if(option)
            return inOrMi * distanceModel.inToMi;
        return inOrMi / distanceModel.inToMi;
    }

    //Ft***************************
    fun ftToYd(ftOrYd: Double, option: Boolean): Double {
        if(option)
            return ftOrYd * distanceModel.ftToYd;
        return ftOrYd / distanceModel.ftToYd;
    }

    fun ftToMi(ftOrMi: Double, option: Boolean): Double {
        if(option)
            return ftOrMi * distanceModel.ftToMi;
        return ftOrMi / distanceModel.ftToMi;
    }

    //Mi***************************
    fun miToYd(miOrYd: Double, option: Boolean): Double {
        if(option)
            return miOrYd * distanceModel.miToYd;
        return miOrYd / distanceModel.miToYd;
    }
}