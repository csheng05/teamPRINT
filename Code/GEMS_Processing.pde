//import the required libraries
import processing.serial.*;

Serial mySerial;
Table table;
String filename;

void setup()
{
  //set mySerial to listen on COM port 10 at 9600 baud
  mySerial = new Serial(this, "/dev/cu.usbmodem141201", 115200); 
  
  table = new Table();
  table.addColumn("Test Time (s)");
  //add a column header "Data" for the collected data
  table.addColumn("F(kg)      millistrain");
}

void draw()
{
  //variables called each time a new data entry is received
  int d = day();
  int m = month();
  int y = year();
  int h = hour();
  int min = minute();
  int s = second();
  int mili = millis();
  
  if(mySerial.available() >= 14)
  {
    //set the value recieved as a String
    String value = mySerial.readString();
    //check to make sure there is a value
    if(value != null)
    {
      //add a new row for each value
      TableRow newRow = table.addRow();
      newRow.setString("Test Time (s)", str(mili/1000.0));
      //place the new row and value under the "Data" column
      newRow.setString("F(kg)      millistrain", value);
    }
  }
}

void keyPressed()
{
  //variables used for the filename timestamp
  int d = day();
  int m = month();
  int h = hour();
  int min = minute();
  int s = second();
  //variable as string under the data folder set as (mm-dd--hh-min-s.csv)
  filename = "/Users/ericoh/Desktop/Testing Data (GEMS)/5/U" + "(" + str(m) + "." + str(d) + ")"+str(h)+":"+str(min)+".csv";
  //save as a table in csv format(data/table - data folder name table)
  saveTable(table, filename);
  exit();
}
