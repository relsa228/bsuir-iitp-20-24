package com.example.quarter_pounder.services.helpers.listeners

import android.view.View
import android.widget.AdapterView
import android.widget.AdapterView.OnItemSelectedListener
import android.widget.EditText
import android.widget.Spinner
import com.example.quarter_pounder.services.helpers.ConverterHelper

class SpinnerHelpListener constructor(inEdit: EditText, outEdit: EditText, inSpin: Spinner,
                                      outSpin: Spinner): OnItemSelectedListener {
    private val inputEdit: EditText
    private val outputEdit: EditText

    private val inputSpinner: Spinner
    private val outputSpinner: Spinner

    init{
        inputEdit = inEdit
        outputEdit = outEdit
        inputSpinner = inSpin
        outputSpinner = outSpin
    }

    override fun onItemSelected(p0: AdapterView<*>?, p1: View?, p2: Int, p3: Long) {
        val converterHelper = ConverterHelper()
        converterHelper.convert(inputEdit, outputEdit, inputSpinner, outputSpinner)
    }

    override fun onNothingSelected(p0: AdapterView<*>?) {
        return
    }
}