package com.example.quarter_pounder.services.helpers.listeners

import android.util.Log
import android.view.View

class TabLongClickListener: View.OnLongClickListener {
    override fun onLongClick(v: View?): Boolean {
        Log.e("ok", "не так сильно, сэмпай!!!")
        return true
    }
}