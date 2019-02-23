package tcpserver;
import java.io.*;
import java.net.*;
public class TCPServer
{
    public static void main(String argv[]) throws Exception
    {
        int workerThreadCount = 0;
        int id = 1;
        ServerSocket welcomeSocket = new ServerSocket(6789);
        while(true)
        {
            Socket connectionSocket = welcomeSocket.accept();
            WorkerThread wt = new WorkerThread(connectionSocket,id);
            Thread t = new Thread(wt);
            t.start();
            workerThreadCount++;
            System.out.println("Client [" + id + "] is now connected. No. of worker threads = " + workerThreadCount);
            id++;
        }
		
    } 
}
class WorkerThread implements Runnable
{
    private Socket connectionSocket;
    private int id;
    public WorkerThread(Socket ConnectionSocket, int id) 
    {
        this.connectionSocket=ConnectionSocket;
        this.id=id;
    }
    public void run()
    {
        String clientSentence;
        String capitalizedSentence;
        while(true)
        {
            try
            {
                DataOutputStream outToServer = new DataOutputStream(connectionSocket.getOutputStream());
                BufferedReader inFromServer = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));    
                clientSentence = inFromServer.readLine();
                capitalizedSentence = clientSentence.toUpperCase();
                outToServer.writeBytes(capitalizedSentence + '\n');
                
            }
            catch(Exception e)
            {
                
            }
        }
    }
}