package prueba2;


import java.util.TimerTask;
import com.fazecast.jSerialComm.*;
import java.nio.charset.*;

public class TimerScheduleHandler extends TimerTask implements SerialPortDataListener{
	
	private final long timeStart;
	
	
	public TimerScheduleHandler(long timeStart) {
		this.timeStart = timeStart;
	}
	
	@Override
	public void run() {
		System.out.println("Time elapsed: " + (System.currentTimeMillis() - this.timeStart) + " milliseconds");
	}

	@Override
	public int getListeningEvents() {
		return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
	}

	@Override
	public void serialEvent(SerialPortEvent event) {
		if(event.getEventType() == SerialPort.LISTENING_EVENT_DATA_RECEIVED) {
			String s = new String(event.getReceivedData(), StandardCharsets.UTF_8);
			System.out.println("DATA: " + s);
		}
	}
	
}
