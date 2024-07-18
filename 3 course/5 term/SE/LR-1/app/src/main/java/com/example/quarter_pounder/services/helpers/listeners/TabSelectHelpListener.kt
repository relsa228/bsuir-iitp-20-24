package com.example.quarter_pounder.services.helpers.listeners

import android.content.Context
import android.content.res.Configuration
import android.widget.ArrayAdapter
import android.widget.EditText
import android.widget.Spinner
import com.example.quarter_pounder.R
import com.google.android.material.tabs.TabLayout
import java.security.AccessController.getContext

class TabSelectHelpListener constructor(appContext: Context, inSpin: Spinner, outSpin: Spinner,
                                        inText: EditText, outText: EditText): TabLayout.OnTabSelectedListener {
    private val applicationContext: Context
    private val inputSpinner: Spinner
    private val outputSpinner: Spinner

    private val inputText: EditText
    private val outputText: EditText

    init {
        applicationContext = appContext
        inputSpinner = inSpin
        outputSpinner = outSpin

        inputText = inText
        outputText = outText
    }

    override fun onTabSelected(tab: TabLayout.Tab?) {
        changeSpinnerList(inputSpinner, outputSpinner, tab!!.position, applicationContext)

        inputText.setText("0")
        outputText.setText("0")
    }

    override fun onTabUnselected(tab: TabLayout.Tab?) {
        return
    }

    override fun onTabReselected(tab: TabLayout.Tab?) {
        return
    }

    private fun changeSpinnerList(inputSpin: Spinner, outputSpin: Spinner, tabId: Int,
                                  appContext: Context) {
        val nightModeFlags: Int = appContext.resources.configuration.uiMode and
                Configuration.UI_MODE_NIGHT_MASK
        var spinner_layout: Int = 0

        when(nightModeFlags) {
            Configuration.UI_MODE_NIGHT_YES -> spinner_layout = R.layout.custom_spinner_layout_dark
            Configuration.UI_MODE_NIGHT_NO -> spinner_layout = R.layout.custom_spinner_layout_light
            Configuration.UI_MODE_NIGHT_UNDEFINED -> spinner_layout = R.layout.custom_spinner_layout_light
        }
        when(tabId) {
            0 -> ArrayAdapter.createFromResource(
                appContext,
                R.array.distance_list,
                spinner_layout
            ).also { adapter ->
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
                inputSpin.adapter = adapter
                outputSpin.adapter = adapter
            };
            1 -> ArrayAdapter.createFromResource(
                appContext,
                R.array.weight_list,
                spinner_layout
            ).also { adapter ->
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
                inputSpin.adapter = adapter
                outputSpin.adapter = adapter
            };
            2 -> ArrayAdapter.createFromResource(
                appContext,
                R.array.data_list,
                spinner_layout
            ).also { adapter ->
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
                inputSpin.adapter = adapter
                outputSpin.adapter = adapter
            };

            3 -> ArrayAdapter.createFromResource(
                appContext,
                R.array.cryptocurrency_list,
                spinner_layout
            ).also { adapter ->
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
                inputSpin.adapter = adapter
                outputSpin.adapter = adapter
            };
        }
    }
}