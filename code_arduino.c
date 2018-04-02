/////////////////////////////////////////
// FIAP - STARTUP ONE 2018            //
// Projeto: BIO Intelligence         //
// Autores: Danilo, Ricardo, Roger  //
/////////////////////////////////////


// Bibliotecas
#include "RTClib.h"	//Relógio Realtime
#include <SPI.h>	
#include <SD.h>		//Cartão de Memória

//Pino CS do cartao SD 
//verificar em qual entrada vai o datalogger 
int Pino_CS = 10;

//podemos parametrizar o intevalo
//alguns lugares pode fazer sentido gravar informação por minuto, outros por hora, etc.
int range_gravacao = 10; //segundos

//parametros de entrada dos sensores (em bits/volts)
int in_temperatura;
int in_umidade;
int in_luminosidade;

//parametros já convertidos para gravação (em unidade Celsius/Percentual)
int out_temperatura;
int out_umidade;
int out_luminosidade;

//parametros do datalogger
RTC_DS1307 rtc;
File file;

//iniciar os serviços
void setup()
{
  Serial.begin(115200);
  Serial.println("Data logger");
  Serial.println();

  //Inicia o cartao SD
  Serial.println("Iniciando cartao SD...");
  if (!SD.begin(Pino_CS))
  {
    Serial.println("Falha na inicializacao do SD!");
    return;
  }
  Serial.println("Cartao SD iniciado. OK");
  Serial.println();
  
  //Verifica as condicoes do RTC
  if (! rtc.begin())
  {
    Serial.println("RTC nao encontrado!");
    while (1);
  }
  if (! rtc.isrunning())
  {
    Serial.println("RTC nao operante!");
    //A linha abaixo ajusta o RTC com a data e hora do momento da compilacao
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //A linha abaixo permite ajustar manualmente a data e hora do RTC
    //Formato: DateTime(ano, mes, dia, hora, minuto, segundo)
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop(void)
{
  String txt_print = ""; 
  	// tem que adicionar todos os sensores aqui
    Serial.println(txt_print.substring(0));
    grava_cartao_SD(txt_print);
    delay(1000*range_gravacao); //10 segundos
    Serial.println();
    Serial.println("Aguardando nova leitura...");
  }


//inserir aspas data_read = '"' + data_read + '"'

void grava_cartao_SD(String txt_print)
{
  //Abre arquivo no SD para gravacao
  file = SD.open("log.txt", FILE_WRITE);
  //Le as informacoes de data e hora
  DateTime now = rtc.now();
  //Grava os dados no cartao SD
  //Falta definir qual o formato que vamos gravar (Json/CSV/TSV)
  file.print("Datahora: ");
  Serial.print(now.day() < 10 ? "0" : "");
  file.print(now.day(), DEC);
  file.print('/');
  file.print(now.month() < 10 ? "0" : "");
  file.print(now.month(), DEC);
  file.print('/');
  file.print(now.year(), DEC);
  file.print(' ');
  file.print(now.hour() < 10 ? "0" : "");
  file.print(now.hour(), DEC);
  file.print(':');
  file.print(now.minute() < 10 ? "0" : "");
  file.print(now.minute(), DEC);
  file.print(':');
  file.print(now.second() < 10 ? "0" : "");
  file.print(now.second(), DEC);
  file.print('; ');
  file.println(txt_print);
  //Fecha arquivo
  file.close();
}





