package prueba2;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;
import java.util.Timer;

import com.fazecast.jSerialComm.SerialPort;

import simon.TimerScheduleHandler;

public class prueba {

    public static void main(String[] args) throws IOException {
        // Archivo de pruebas:
        // C:\Users\Ocon\Desktop\A.txt
        String rutaFija = "C:\\Users\\cimbo\\OneDrive\\Escritorio\\";
        Scanner sc = new Scanner(System.in);
        System.out.println("Bienvenido al Super Simón Dice. Mucha suerte!!!");
        System.out.println("Inserte su nombre de usuario: ");
        String nombreJugador = sc.nextLine();
        System.out.println("Inserte fecha: ");
        String fecha = sc.nextLine();
        String archivoOrigenFinal = rutaFija + nombreJugador + ".txt";
        

        //System.out.println(archivoOrigenFinal);

        File f = new File(archivoOrigenFinal);
        OutputStream os = new FileOutputStream(f, true);
        OutputStreamWriter osw = new OutputStreamWriter(os, StandardCharsets.UTF_8);
        PrintWriter pw = new PrintWriter(osw);

        
        long timeStart = System.currentTimeMillis();
		SerialPort sp = SerialPort.getCommPort("COM3");
		sp.setComPortParameters(9600,  Byte.SIZE, SerialPort.ONE_STOP_BIT, SerialPort.NO_PARITY);
		sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		boolean isOpened = sp.openPort();
		if(!isOpened) {
			throw new IllegalStateException("Failed to open serial port");
		}
		
		Timer timer = new Timer();
		TimerScheduleHandler timedSchedule = new TimerScheduleHandler(timeStart);
		
		sp.addDataListener(timedSchedule);
		
		System.out.println( "animo con la partida, empiezaa jugar! Recuerde que cuando quiera terminar su partida solo tendrá que parar la consola");
		
		pw.println(fecha);
		OutputStream autoFlush;
		boolean append = true;
		PrintStream out = new PrintStream(
		        new FileOutputStream(archivoOrigenFinal, append));
		System.setOut(out);
		//:
        
        //System.out.println("Escriba una frase: ");
        //String nuevaFrase = sc.nextLine();
        
        /*while (!nuevaFrase.equals("SALIR")) {
            pw.println(nuevaFrase);
            System.out.println("Escriba otra frase: ");
            nuevaFrase = sc.nextLine();

        }*/
        //System.out.println("Ha salido de la app correctamente");
        
        //System.out.println("Escriba SALIR para terminar la partida: ");
        //String salir = sc.nextLine();
        
        
        pw.close();
        osw.close();
        os.close();
        sc.close();

    }

}