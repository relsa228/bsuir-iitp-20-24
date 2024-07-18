package com.example.quarter_pounder

import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.LinearLayout
import android.widget.Spinner
import androidx.appcompat.app.AppCompatActivity
import com.example.quarter_pounder.services.database.services.DatabasePushServices
import com.example.quarter_pounder.services.helpers.ConverterHelper
import com.example.quarter_pounder.services.helpers.UiHelper
import com.example.quarter_pounder.services.helpers.listeners.SpinnerHelpListener
import com.example.quarter_pounder.services.helpers.listeners.TabSelectHelpListener
import com.example.quarter_pounder.ui.main.MainFragment
import com.google.android.material.tabs.TabLayout

private val update = DatabasePushServices()

class MainActivity : AppCompatActivity() {
    private lateinit var uiHelper: UiHelper;
    private val converterHelper = ConverterHelper()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_activity)
        if (savedInstanceState == null) {
            supportFragmentManager.beginTransaction()
                    .replace(R.id.container, MainFragment.newInstance())
                    .commitNow()
        }
    }
    override fun onStart() {
        super.onStart()
        update.initDb(this.applicationContext)

        this.uiHelper = UiHelper(this.applicationContext);

        val inputSpinner: Spinner = findViewById(R.id.InputSpinner)
        val outputSpinner: Spinner = findViewById(R.id.OutputSpinner)
        val inputText: EditText = findViewById(R.id.input)
        val outputText: EditText = findViewById(R.id.output)
        val tabLayout: TabLayout = findViewById(R.id.TabUnits);



        val spinnerListener = SpinnerHelpListener(inputText, outputText,
            inputSpinner, outputSpinner);
        inputSpinner.onItemSelectedListener = spinnerListener
        outputSpinner.onItemSelectedListener = spinnerListener

        val tabSelectHelpListener = TabSelectHelpListener(this.applicationContext, inputSpinner,
            outputSpinner, inputText, outputText);
        tabLayout.addOnTabSelectedListener(tabSelectHelpListener)

        val tabs = tabLayout.getChildAt(0) as LinearLayout

        for (i in 0 until tabs.childCount) {
            when(i){
                0 -> tabs.getChildAt(0).setOnLongClickListener { true }
                1 -> tabs.getChildAt(1).setOnLongClickListener { true }
                2 -> tabs.getChildAt(2).setOnLongClickListener { true }
                3 -> tabs.getChildAt(3).setOnLongClickListener {
                    update.dbUpdate(this.applicationContext)
                    converterHelper.convert(inputText, outputText, inputSpinner, outputSpinner)
                    true
                }
            }
        }
    }
    fun numBtnOnClick(view: View) {
        val inputEditText: EditText = findViewById(R.id.input);
        var inputVal = "";
        when(view.id) {
            R.id.b0 -> inputVal = uiHelper.inputValidation("0", inputEditText.text.toString());
            R.id.b00 -> inputVal = uiHelper.inputValidation("00", inputEditText.text.toString());
            R.id.b1 -> inputVal = uiHelper.inputValidation("1", inputEditText.text.toString());
            R.id.b2 -> inputVal = uiHelper.inputValidation("2", inputEditText.text.toString());
            R.id.b3 -> inputVal = uiHelper.inputValidation("3", inputEditText.text.toString());
            R.id.b4 -> inputVal = uiHelper.inputValidation("4", inputEditText.text.toString());
            R.id.b5 -> inputVal = uiHelper.inputValidation("5", inputEditText.text.toString());
            R.id.b6 -> inputVal = uiHelper.inputValidation("6", inputEditText.text.toString());
            R.id.b7 -> inputVal = uiHelper.inputValidation("7", inputEditText.text.toString());
            R.id.b8 -> inputVal = uiHelper.inputValidation("8", inputEditText.text.toString());
            R.id.b9 -> inputVal = uiHelper.inputValidation("9", inputEditText.text.toString());
        }
        inputEditText.setText(inputVal)
        converterHelper.convert(inputEditText, findViewById(R.id.output), findViewById(R.id.InputSpinner),
            findViewById(R.id.OutputSpinner))
    }
    fun toolBtnOnClick(view: View) {
        val dataManager: ClipboardManager = this.applicationContext
            .getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
        var data: ClipData? = dataManager.primaryClip

        val inputEditText: EditText = findViewById(R.id.input);
        val outputEditText: EditText = findViewById(R.id.output);
        val inputSpin: Spinner = findViewById(R.id.InputSpinner);
        val outputSpin: Spinner = findViewById(R.id.OutputSpinner);

        when(view.id) {
            R.id.cleanInput -> {
                inputEditText.setText("0")
                outputEditText.setText("0")
            };
            R.id.switchValues -> uiHelper.switchValues(inputEditText, outputEditText, inputSpin, outputSpin);
            R.id.copy -> uiHelper.copyToClipboard(inputEditText.text.toString(),
                outputEditText.text.toString(), inputSpin.selectedItem.toString(), outputSpin.selectedItem.toString());
            R.id.comma -> inputEditText.setText(uiHelper.inputValidation(".", inputEditText.text.toString()));
            R.id.delete -> {
                uiHelper.deleteCh(inputEditText)
                converterHelper.convert(inputEditText, outputEditText, inputSpin, outputSpin)
            }
        }
    }

    fun onPaste(){

    }
}