package com.example.quarter_pounder.services.helpers

import android.widget.EditText
import android.widget.Spinner
import com.example.quarter_pounder.models.UnitSigns
import com.example.quarter_pounder.services.converters.CryptocurrencyConverter
import com.example.quarter_pounder.services.converters.DataConverter
import com.example.quarter_pounder.services.converters.DistanceConverter
import com.example.quarter_pounder.services.converters.WeightConverter

class ConverterHelper {
    fun convert(inputNum: EditText, outNum: EditText, fSpin: Spinner, sSpin: Spinner) {
        var fSign: UnitSigns = UnitSigns.B
        var sSign: UnitSigns = UnitSigns.B

        UnitSigns.values().forEach {
            if (it.nameOfUnit == fSpin.selectedItem.toString())
                fSign = it
            if (it.nameOfUnit == sSpin.selectedItem.toString())
                sSign = it
        }

        if (fSign == UnitSigns.M || fSign == UnitSigns.FT || fSign == UnitSigns.IN ||
            fSign == UnitSigns.YD || fSign == UnitSigns.MI)
            distanceConvertHelper(inputNum, outNum, fSign, sSign)

        else if (fSign == UnitSigns.BIT || fSign == UnitSigns.B || fSign == UnitSigns.KB ||
            fSign == UnitSigns.MB)
            dataConvertHelper(inputNum, outNum, fSign, sSign)

        else if (fSign == UnitSigns.KG || fSign == UnitSigns.T || fSign == UnitSigns.OZ ||
            fSign == UnitSigns.LB)
            weightConvertHelper(inputNum, outNum, fSign, sSign)

        else if (fSign == UnitSigns.ETH || fSign == UnitSigns.LTC || fSign == UnitSigns.BTC)
            cryptocurrencyConvertHelper(inputNum, outNum, fSign, sSign)
    }
    private fun distanceConvertHelper(inputNum: EditText, outNum: EditText, fSign: UnitSigns, sSign: UnitSigns) {
        val inputStr: String = inputNum.text.toString()
        val inputN: Double = inputStr.toDouble()

        val distanceConverter: DistanceConverter = DistanceConverter()

        when (fSign) {
            UnitSigns.M -> {
                when (sSign) {
                    UnitSigns.M -> outNum.setText(inputStr)
                    UnitSigns.FT -> outNum.setText(distanceConverter.meterToFt(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.IN -> outNum.setText(distanceConverter.meterToIn(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.YD -> outNum.setText(distanceConverter.meterToYd(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MI -> outNum.setText(distanceConverter.meterToMi(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.FT -> {
                when (sSign) {
                    UnitSigns.M -> outNum.setText(distanceConverter.meterToFt(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.FT -> outNum.setText(inputStr)
                    UnitSigns.IN -> outNum.setText(distanceConverter.inToFt(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.YD -> outNum.setText(distanceConverter.ftToYd(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MI -> outNum.setText(distanceConverter.ftToMi(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.IN -> {
                when (sSign) {
                    UnitSigns.M -> outNum.setText(distanceConverter.meterToIn(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.FT -> outNum.setText(distanceConverter.inToFt(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.IN -> outNum.setText(inputStr)
                    UnitSigns.YD -> outNum.setText(distanceConverter.inToYd(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MI -> outNum.setText(distanceConverter.inToMi(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.YD -> {
                when (sSign) {
                    UnitSigns.M -> outNum.setText(distanceConverter.meterToYd(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.FT -> outNum.setText(distanceConverter.ftToYd(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.IN -> outNum.setText(distanceConverter.inToYd(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.YD -> outNum.setText(inputStr)
                    UnitSigns.MI -> outNum.setText(distanceConverter.miToYd(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.MI -> {
                when (sSign) {
                    UnitSigns.M -> outNum.setText(distanceConverter.meterToMi(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.FT -> outNum.setText(distanceConverter.ftToMi(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.IN -> outNum.setText(distanceConverter.inToMi(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.YD -> outNum.setText(distanceConverter.miToYd(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MI -> outNum.setText(inputStr)
                    else -> {}
                }
                return;
            }

            else -> {}
        }
    }

    private fun dataConvertHelper(inputNum: EditText, outNum: EditText, fSign: UnitSigns, sSign: UnitSigns) {
        val inputStr: String = inputNum.text.toString()
        val inputN: Double = inputStr.toDouble()

        val dataConverter: DataConverter = DataConverter()

        when (fSign) {
            UnitSigns.BIT -> {
                when (sSign) {
                    UnitSigns.BIT -> outNum.setText(inputStr)
                    UnitSigns.B -> outNum.setText(dataConverter.bitsToBytes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.KB -> outNum.setText(dataConverter.bitsToKilobytes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MB -> outNum.setText(dataConverter.bitsToMegabytes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.B -> {
                when (sSign) {
                    UnitSigns.BIT -> outNum.setText(dataConverter.bitsToBytes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.B -> outNum.setText(inputStr)
                    UnitSigns.KB -> outNum.setText(dataConverter.bytesToKilobytes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MB -> outNum.setText(dataConverter.bytesToMegabytes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.KB -> {
                when (sSign) {
                    UnitSigns.BIT -> outNum.setText(dataConverter.bitsToKilobytes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.B -> outNum.setText(dataConverter.bytesToKilobytes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.KB -> outNum.setText(inputStr)
                    UnitSigns.MB -> outNum.setText(dataConverter.kilobytesToMegabytes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.MB -> {
                when (sSign) {
                    UnitSigns.BIT -> outNum.setText(dataConverter.bitsToMegabytes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.B -> outNum.setText(dataConverter.bytesToMegabytes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.KB -> outNum.setText(dataConverter.kilobytesToMegabytes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.MB -> outNum.setText(inputStr)
                    else -> {}
                }
                return;
            }

            else -> {}
        }
    }

    private fun weightConvertHelper(inputNum: EditText, outNum: EditText, fSign: UnitSigns, sSign: UnitSigns) {
        val inputStr: String = inputNum.text.toString()
        val inputN: Double = inputStr.toDouble()

        val weightConverter: WeightConverter = WeightConverter()

        when (fSign) {
            UnitSigns.KG -> {
                when (sSign) {
                    UnitSigns.KG -> outNum.setText(inputStr)
                    UnitSigns.T -> outNum.setText(weightConverter.killogrammsToTonnes(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.OZ -> outNum.setText(weightConverter.killogrammsToOunce(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.LB -> outNum.setText(weightConverter.killogrammsToLb(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.T -> {
                when (sSign) {
                    UnitSigns.KG -> outNum.setText(weightConverter.killogrammsToTonnes(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.T -> outNum.setText(inputStr)
                    UnitSigns.OZ -> outNum.setText(weightConverter.tonneToOunce(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.LB -> outNum.setText(weightConverter.lbToOunce(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.OZ -> {
                when (sSign) {
                    UnitSigns.KG -> outNum.setText(weightConverter.killogrammsToOunce(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.T -> outNum.setText(weightConverter.tonneToOunce(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.OZ -> outNum.setText(inputStr)
                    UnitSigns.LB -> outNum.setText(weightConverter.lbToOunce(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.LB -> {
                when (sSign) {
                    UnitSigns.KG -> outNum.setText(weightConverter.killogrammsToLb(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.T -> outNum.setText(weightConverter.tonneToLb(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.OZ -> outNum.setText(weightConverter.lbToOunce(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.LB -> outNum.setText(inputStr)
                    else -> {}
                }
                return;
            }

            else -> {}
        }
    }

    private fun cryptocurrencyConvertHelper(inputNum: EditText, outNum: EditText, fSign: UnitSigns, sSign: UnitSigns) {
        val inputStr: String = inputNum.text.toString()
        val inputN: Double = inputStr.toDouble()

        val cryptocurrencyConverter = CryptocurrencyConverter()

        when (fSign) {
            UnitSigns.ETH -> {
                when (sSign) {
                    UnitSigns.ETH -> outNum.setText(inputStr)
                    UnitSigns.LTC -> outNum.setText(cryptocurrencyConverter.ethToLTC(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.BTC -> outNum.setText(cryptocurrencyConverter.ethToBTC(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.LTC -> {
                when (sSign) {
                    UnitSigns.ETH -> outNum.setText(cryptocurrencyConverter.ethToLTC(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.LTC -> outNum.setText(inputStr)
                    UnitSigns.BTC -> outNum.setText(cryptocurrencyConverter.ltcToBTC(inputN, true)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    else -> {}
                }
                return;
            }
            UnitSigns.BTC -> {
                when (sSign) {
                    UnitSigns.ETH -> outNum.setText(cryptocurrencyConverter.ethToBTC(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.LTC -> outNum.setText(cryptocurrencyConverter.ltcToBTC(inputN, false)
                        .toBigDecimal().stripTrailingZeros().toPlainString())
                    UnitSigns.BTC -> outNum.setText(inputStr)
                    else -> {}
                }
                return;
            }

            else -> {}
        }
    }
}