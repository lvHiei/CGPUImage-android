package com.lvhiei.cgpuimage;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ListFilterActivity extends Activity {

    private ListView mFilterList;

    private Map<Integer, Integer> mFiltetMap = new HashMap<>();
    private Map<String, Integer> mFiltetNameMap = new HashMap<>();

    private AdapterView.OnItemClickListener mItemClickListener = new AdapterView.OnItemClickListener(){

        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            Log.i("Tag", "onItemClick view:" + view.getId() + ",pos:" + position + ",id:" + id);
            Intent intent = new Intent(ListFilterActivity.this, MainActivity.class);

            Bundle bundle = new Bundle();
            bundle.putInt("filterid", position);

            intent.putExtras(bundle);

            startActivity(intent);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_filter);

        initView();
    }

    private void initView(){
        mFilterList = (ListView) findViewById(R.id.cgpuimage_filterList);
        ArrayAdapter adapter = new ArrayAdapter<String>(this,  R.layout.vlist, getData());
//        ArrayAdapter adapter = new ArrayAdapter<String>(this,  android.R.layout.simple_expandable_list_item_1, getData());
//        ArrayAdapter adapter = new ArrayAdapter<String>(this,  android.R.layout.simple_expandable_list_item_2, getData());
//        SimpleAdapter adapter = new SimpleAdapter(this, )
        mFilterList.setAdapter(adapter);

        mFilterList.setOnItemClickListener(mItemClickListener);
    }

    private List<String> getData(){
        List<String> data = new ArrayList<>();


        data.add("3X3 convolution");

        data.add("adaptive threshold");
        data.add("add blend");
        data.add("alpha blend");
        data.add("amatorka");

        data.add("bilateral");
        data.add("boxblur");
        data.add("brightness");
        data.add("bulge distortion");

        data.add("canny edge detection");
        data.add("CGA colorspace");
        data.add("chromakey blend");
        data.add("chromakey");
        data.add("closing");
        data.add("color blend");
        data.add("color burn blend");
        data.add("color dodge blend");
        data.add("color invert");
        data.add("color local binary pattern");
        data.add("color matrix");
        data.add("color packing");
        data.add("colour FAST feature detector");
        data.add("colour FAST sampling operation");
        data.add("contrast");
        data.add("crop");
        data.add("crosshatch");

        data.add("darken blend");
        data.add("difference blend");
        data.add("dilation");
        data.add("directional non maximum suppression");
        data.add("directional sobel edge detection");
        data.add("dissolve blend");
        data.add("divide blend");


        data.add("emboss");
        data.add("erosion");
        data.add("exclusion blend");
        data.add("exposure");

        data.add("false color");

        data.add("gamma");
        data.add("gaussian blur");
        data.add("gaussian blur position");
        data.add("gaussian selective blur");
        data.add("glass sphere");
        data.add("greyscale");

        data.add("halftone");
        data.add("hard light blend");
        data.add("haze");
        data.add("highlight shadow");
        data.add("highlight shadow tint");
        data.add("HSB");
        data.add("hue blend");
        data.add("hue");

        data.add("ios blure");

        data.add("JFA voronoi");

        data.add("kuwahara");
        data.add("kuwahara radius3");

        data.add("lanczos resampling");
        data.add("laplacian");
        data.add("levels");
        data.add("lighten blend");
        data.add("linear burn blend");
        data.add("local binary pattern");
        data.add("luminance range");
        data.add("luminance threshold");
        data.add("luminosity blend");

        data.add("mask");
        data.add("median");
        data.add("miss etikate");
        data.add("monochrome");
        data.add("mosaic");
        data.add("motion blur");
        data.add("multiply blend");

        data.add("non maximum suppression");
        data.add("normal blend");

        data.add("opacity");
        data.add("opening");
        data.add("overlay blend");

        data.add("perlin noise");
        data.add("pinch distortion");
        data.add("pixellate");
        data.add("pixellate position");
        data.add("poisson blend");
        data.add("polar pixellate");
        data.add("polka dot");
        data.add("posterize");
        data.add("prewitt edge detection");

        //

        data.add("RGB closing");
        data.add("RGB dilation");
        data.add("RGB erosion");
        data.add("RGB");
        data.add("RGB opening");

        data.add("saturation blend");
        data.add("saturation");
        data.add("screen blend");
        data.add("sepia");
        data.add("sharpen");
        data.add("single component gaussian blur");
        data.add("sketch");
        data.add("skin tone");
        data.add("smooth toon");
        data.add("sobel edge detection");
        data.add("soft elegance");
        data.add("soft light blend");
        data.add("source over blend");
        data.add("sphere refraction");
        data.add("stretch distortion");
        data.add("subtract blend");
        data.add("swirl");

        data.add("threshold edge detection");
        data.add("thresholded non maximum suppression");
        data.add("threshold sketch");
        data.add("tilt shift");
        data.add("tone curve");
        data.add("toon");
        data.add("transform");

        data.add("unsharp mask");

        data.add("vibrance");
        data.add("vignette");
        data.add("voronoi consumer");

        data.add("weak pixel inclusion");
        data.add("white balance");

        data.add("XY derivative");

        data.add("zoom");

        return data;
    }


}
