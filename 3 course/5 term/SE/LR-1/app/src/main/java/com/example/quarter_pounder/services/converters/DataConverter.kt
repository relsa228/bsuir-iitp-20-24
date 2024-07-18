package com.example.quarter_pounder.services.converters

import com.example.quarter_pounder.models.DataModel

class DataConverter {
    private val dataModel: DataModel = DataModel();

    //Bits***************************
    fun bitsToBytes(bitsOrBytesCount: Double, option: Boolean): Double {
        if(option)
            return bitsOrBytesCount * dataModel.bitsToBytes;
        return bitsOrBytesCount / dataModel.bitsToBytes;
    }

    fun bitsToKilobytes(bitsOrKilobytesCount: Double, option: Boolean): Double {
        if(option)
            return bitsOrKilobytesCount * dataModel.bitsToKilobytes;
        return bitsOrKilobytesCount / dataModel.bitsToKilobytes;
    }

    fun bitsToMegabytes(bitsOrMegabytesCount: Double, option: Boolean): Double {
        if(option)
            return bitsOrMegabytesCount * dataModel.bitsToMegabytes;
        return bitsOrMegabytesCount / dataModel.bitsToMegabytes;
    }

    //Bytes***************************
    fun bytesToKilobytes(bitsOrKilobytesCount: Double, option: Boolean): Double {
        if(option)
            return bitsOrKilobytesCount * dataModel.bytesToKilobytes;
        return bitsOrKilobytesCount / dataModel.bytesToKilobytes;
    }

    fun bytesToMegabytes(bitsOrKilobytesCount: Double, option: Boolean): Double {
        if(option)
            return bitsOrKilobytesCount * dataModel.bytesToMegabytes;
        return bitsOrKilobytesCount / dataModel.bytesToMegabytes;
    }

    //Kilobytes***************************
    fun kilobytesToMegabytes(bitsOrKilobytesCount: Double, option: Boolean): Double {
        if(option)
            return bitsOrKilobytesCount * dataModel.kilobytesToMegabytes;
        return bitsOrKilobytesCount / dataModel.kilobytesToMegabytes;
    }
}