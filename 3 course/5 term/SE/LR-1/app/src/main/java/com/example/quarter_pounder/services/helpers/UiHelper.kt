package com.example.quarter_pounder.services.helpers

import android.content.ClipData
import android.content.ClipboardManager
import android.content.Context
import android.widget.EditText
import android.widget.Spinner
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity

import com.example.quarter_pounder.models.UnitSigns

class UiHelper(private var context: Context) : AppCompatActivity() {
    fun switchValues(inputEditText: EditText, outputEditText: EditText, inputSpin: Spinner,
    outputSpin: Spinner) {
        val tempStr: String = inputEditText.text.toString();

        inputEditText.setText(outputEditText.text.toString());
        outputEditText.setText(tempStr);

        val tempId: Int = inputSpin.selectedItemId.toInt()
        inputSpin.setSelection(outputSpin.selectedItemId.toInt(), true)
        outputSpin.setSelection(tempId, true)
    }

    fun inputValidation(inputNum: String, currentNum: String): String {
        if (currentNum.length >= 30){
            Toast.makeText(context, "Допускается не более 30 символов", Toast.LENGTH_SHORT).show();
            return currentNum;
        }
        var mantissaCount = 0;
        var mantissaFlag = false;
        currentNum.forEach {
            if(it == '.')
                mantissaFlag = true;
            if(mantissaFlag)
                mantissaCount++;
        }
        if (mantissaCount >= 15){
            Toast.makeText(context, "Допускается не более 15 знаков после запятой", Toast.LENGTH_SHORT).show();
            return currentNum;
        }

        if (inputNum[0] == '0') {
            var nullFlag = true;
            currentNum.forEach {
                if (it != '0') {
                    nullFlag = false
                    return@forEach;
                };
            }
            if (nullFlag)
                return "0"
            return currentNum + inputNum;
        };
        else if (inputNum == "." && currentNum.length < 29) {
            var commaFlag = false;
            currentNum.forEach {
                if (it == '.') {
                    commaFlag = true;
                    return@forEach;
                }
            }
            if (commaFlag)
                return currentNum;
            return currentNum + inputNum;
        };
        else if (inputNum == ".")
            return currentNum;
        if (currentNum == "0")
            return inputNum;
        return currentNum + inputNum;
    }

    fun copyToClipboard(input: String, output: String, fUnit: String, sUnit: String) {
        var funitSign = ""
        var sunitSign = ""

        UnitSigns.values().forEach {
            if (it.nameOfUnit == fUnit)
                funitSign = it.name
            if (it.nameOfUnit == sUnit)
                sunitSign = it.name
        }

        val clipboard = context.getSystemService(Context.CLIPBOARD_SERVICE) as ClipboardManager
        val clip = ClipData.newPlainText("label", "$input $funitSign = $output $sunitSign")
        clipboard.setPrimaryClip(clip)

        Toast.makeText(context, "Результат вычислений скопирован", Toast.LENGTH_SHORT).show()
    }

    fun deleteCh(textInput: EditText) {
        var input = textInput.text.toString()

        if (input.length == 1) textInput.setText("0")
        else {
            input = input.dropLast(1);
            if (input.last() == 'E')
                input = input.dropLast(1);
            else if (input.last() == '-')
                input = input.dropLast(2);
            textInput.setText(input)
        }
    }
}