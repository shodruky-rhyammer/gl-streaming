package com.kdt.glstreamserver;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.opengl.*;
import android.app.*;
import android.content.*;
import android.view.*;
import android.widget.*;
import android.view.ContextMenu.*;
import java.io.*;
import android.util.*;

public class GLStreamingActivity extends Activity
{
	private GLStreamingView mGLSurface;
	private AlertDialog createdDialog;
	private LinearLayout logLayout;
	private ScrollView logScroll;
	private TextView logText;
	@Override
    public void onCreate(Bundle savedInstanceState)
    {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		logLayout = (LinearLayout) findViewById(R.id.main_glstream_logview);
		logScroll = (ScrollView) findViewById(R.id.main_glstream_log_scroll);
		logText = (TextView) logScroll.getChildAt(0);
		
		new Thread(new Runnable(){
			@Override
			public void run() {
				try {
					String[] command = new String[] { "logcat"};

					Process process = Runtime.getRuntime().exec(command);

					BufferedReader bufferedReader = new BufferedReader(
						new InputStreamReader(process.getInputStream()));

					final String line;
					while ((line = bufferedReader.readLine()) != null) {
						logText.post(new Runnable(){

								@Override
								public void run()
								{
									logText.append(line + "\n");
								}
							});
					}
				} catch (IOException ex) {
					Log.e("GLStream", "getLog failed", ex);
				}
			}
		}, "LogcatThread").start();
		
		System.out.println("The PID of GL Streaming server: " + android.os.Process.myPid());
		
		mGLSurface = (GLStreamingView) findViewById(R.id.main_glstream_surfaceview);
		
		AlertDialog.Builder dialog = new AlertDialog.Builder(this);
		dialog.setTitle(R.string.app_name);
		dialog.setView(R.layout.config);
		dialog.setPositiveButton(android.R.string.ok, null);
		dialog.setNegativeButton("Exit", new DialogInterface.OnClickListener(){

				@Override
				public void onClick(DialogInterface i, int p2) {
					finish();
				}
			});
		dialog.setCancelable(false);
		createdDialog = dialog.create();
		createdDialog.setOnShowListener(new DialogInterface.OnShowListener(){

				@Override
				public void onShow(DialogInterface p1)
				{
					final EditText editServerPort = (EditText) createdDialog.findViewById(R.id.config_edittext_serverport);
					final EditText editClientAddr = (EditText) createdDialog.findViewById(R.id.config_edittext_clientaddr);

					createdDialog.getButton(AlertDialog.BUTTON_POSITIVE).setOnClickListener(new View.OnClickListener(){
						@Override
						public void onClick(View p1) {
							String serverPortStr = editServerPort.getText().toString();
							int serverPort = 18145;
							String clientAddr = editClientAddr.getText().toString();
							String outClientAddr = "127.0.0.1";
							int outClientPort = 18146;
							
							if (serverPortStr.isEmpty()) {
								// Default server port
							} else if (serverPortStr.length() > 5) {
								editServerPort.setError("Server port is too long!");
								return;
							} else {
								serverPort = Integer.parseInt(serverPortStr);
							}
							if (clientAddr.isEmpty()) {
								// Default client address and port
							} else if (clientAddr.contains(":")) {
								String[] clientAddrPort = clientAddr.split(":");
								// Check if contains more than one ":".
								if (clientAddrPort.length > 2) {
									editClientAddr.setError("Must be only one \":\"");
									return;
								}

								if (!clientAddrPort[0].isEmpty()) outClientAddr = clientAddrPort[0];
								if (!clientAddrPort[1].isEmpty()) outClientPort = Integer.parseInt(clientAddrPort[1]);
							} else {
								outClientAddr = clientAddr;
							}

							createdDialog.dismiss();
							
							mGLSurface.init(/* true, */ serverPort, outClientAddr, outClientPort);
						}
					});
				}
			});
		createdDialog.show();
	}
	
	public void closeLog(View v) {
		logLayout.setVisibility(View.GONE);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		// Handle item selection
		switch (item.getItemId()) {
			case R.id.menu_serverlog:
				logLayout.setVisibility(View.VISIBLE);
				return true;
			default:
				return super.onOptionsItemSelected(item);
		}
	}
	
    @Override
	protected void onPause() {
        super.onPause();
        // mGLSurface.onPause();
    }

    @Override
	protected void onResume() {
        super.onResume();
        // mGLSurface.onResume();
    }
}
