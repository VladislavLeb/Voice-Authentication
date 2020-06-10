#pragma once
#include "bass.h"
//#include <vcl.h>
//#include <commctrl.h>
//#include <stdlib.h>
#include "stdafx.h"
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <msclr\marshal_cppstd.h>
//#pragma hdrstop
#pragma comment(lib,"bass.lib")


namespace fftprog {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

FILE *datafile;

HSTREAM HStream; //Дескриптор потока
float buffer[128]; //Буфер для БПФ аудио
float Summator[128]; //Массив сумм частот БПФ
float Around[128]; //Массив средних значений частот
float c = 0; //Счетчик количества слагаемых сумм

float rezultmas[128]; 
char *recbuf=NULL;
string rezstr;
HRECORD rchan=0;
DWORD reclen;	
HSTREAM chan=0;	
float mvoice[128]; 

int StartPosition;
double Length = 0;
bool TrackBarMoove = false;
bool findv = false;
#define FREQ 44100
#define CHANS 2
#define BUFSTEP 200000



	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timer2;




	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	private: System::Windows::Forms::Button^  button3;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(246, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Выбрать аудиофайл с голосом";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(266, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(246, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Сохранить в файл результат разложения";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(266, 41);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(246, 23);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Сделать аудиозапись голоса";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(12, 41);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(246, 23);
			this->button5->TabIndex = 11;
			this->button5->Text = L"Сравнить голоса";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(206, 109);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(121, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"(результат сравнения)";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(537, 32);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(162, 102);
			this->richTextBox1->TabIndex = 14;
			this->richTextBox1->Text = L"";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(197, 82);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(141, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Имя файла пользователя:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(534, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(158, 13);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Результаты поиска в файлах:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(711, 141);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Система идентификации пользователя по голосу";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				  if (!(BASS_Init(-1,44100,BASS_DEVICE_8BITS,0,NULL)))
					  MessageBox::Show("ХЗ", "ХЗ",MessageBoxButtons::OK,MessageBoxIcon::Asterisk);
					//  ShowMessage("Can't initialize BASS!");
//        BASS_SetVolume((float)(trackBar2->Value)/100);
//        Chart1->DoubleBuffered = true;


			 }






private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {

			
			 BASS_Free();
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {//	 BASS_Free();
			 if (timer1->Enabled==false) {timer1->Enabled=true;}

 BASS_ChannelStop(HStream);
        c = 0;
        //Создаем поток из аудиофайла
        if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
         String^ str3= openFileDialog1->FileName;
		std::string result = msclr::interop::marshal_as<std::string>(str3);
		// string str = str3;
		//AnsiString str1 = str3;
        HStream = BASS_StreamCreateFile(FALSE, result.c_str(), 0, 0, 0);
        }
        //Определяем длину аудиофайла в секундах
        Length = BASS_ChannelGetLength(HStream,BASS_POS_BYTE);
//        Label4->Caption = floor(BASS_ChannelBytes2Seconds(HStream,Length));
//        TrackBar2->Max = Length;
        //Проигрываем поток
        BASS_ChannelPlay(HStream,0);
        //Обнуляем массив сумм и средних значений БПФ и буфер
        for (int i = 0; i < 128; i++){
                Summator[i] = 0;
                Around[i] = 0;
                buffer[i] = 0;
				rezultmas[i]=0;
        }


		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
 //Записываем в буфер БПФ аудиофайла
        BASS_ChannelGetData(HStream,buffer,BASS_DATA_FFT256);
        //Вычисляем средние значения частот
      float s=0;
		for (int i = 0; i < 128; i++){
              
				s=s+buffer[i];
		}
		if (s>0.2)
		{
		c++;
  /*      for (int i = 0; i < 128; i++){
                Summator[i] += buffer[i];
                Around[i] = Summator[i] / c;
				rezultmas[i]=rezultmas[i]+Around[i];*/

				
				//sprintf(rezchar, "%f", Around[i]);
//		std::string f_str2 = std::to_string(Around[i]);
	//			textBox1->Text=f_str2;
     //   }
		for (int i = 0; i < 128; i++){
              
				rezultmas[i]=rezultmas[i]+buffer[i];
		}
		}
        //Отображаем данные на графике
        //Средние значения частот БПФ
        //if (CheckBox1->Checked){
      //  Series1->Clear();
       // for (int i = 0; i < 128; i++){
         //       Series1->AddXY(i,Around[i],"",clLime);
        
       // }
       // if (!TrackBarMoove){
        //TrackBar2->Position = BASS_ChannelGetPosition(HStream,BASS_POS_BYTE);
        //if (TrackBar2->Position == Length) {BASS_ChannelSetPosition(HStream,0,BASS_POS_BYTE); BASS_ChannelPlay(HStream,0);}
       // }

			


		 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

//String^ str3= openFileDialog1->FileName;
			 timer1->Enabled=false;
	//	std::string result = msclr::interop::marshal_as<std::string>(str3);
			 	for (int i = 0; i < 128; i++){
              
				rezultmas[i]=rezultmas[i]/c;
		}
			   if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
       String^ str4 = saveFileDialog1->FileName + ".txt";
	   std::string str5 = msclr::interop::marshal_as<std::string>(str4);
        if ((datafile = fopen(str5.c_str(),"wt")) == 0) {}
        else {
        for (int i = 0; i < 128; i++){
                fprintf(datafile,"%f\n",rezultmas[i]);

        }
		FILE * mainf=fopen("main.txt","a"); 
fputs(str5.c_str(), mainf);
fputs("\n", mainf);
   fclose(mainf);
        fclose(datafile);
        }
        }


		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {


WinExec( "rectest.exe", 1);
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
/*	FILE * pFile;
char mystring [128];

pFile = fopen ("main.txt" , "r");
if (pFile == NULL) perror ("Error opening file");
while( fgets (mystring , 128 , pFile) != NULL )
{
for(int i=0;i<strlen(mystring);i++)
if(mystring[i] == '\n') mystring[i] = '\0';


}
sum=mystring[1];
fclose (pFile);

    vector<string> arr;
    vector<string>::iterator i;
    ifstream ifs;
    string str;
    
    ifs.open("main.txt");
   
    
    while ( !ifs.eof() ){
        getline(ifs, str);
        arr.push_back(str);
    }
    
    ifs.close();
    
    for ( i = arr.begin(); i != arr.end(); i++ )
        line[1]=*i;*/

 int n = 0; 
    ifstream file("main.txt"); 
  
    while (file >> mvoice[n]) ++n; 
 
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 richTextBox1->Text="";
			 timer1->Enabled=false;
			 	for (int i = 0; i < 128; i++){
              
				rezultmas[i]=rezultmas[i]/c;
		}
			 
			 int schet=0;
			 ifstream inFile ("main.txt");
	ofstream outFile ("output2.txt");
	int count=0;
	char str[20][255];
	char tmp[255];
	float srav=0;
	findv=false;
	float finalrezult=0.4;
  float SumMvoice=0, SumResultmas=0;
	while(inFile.getline(tmp,255,'\n'))	//или get(tmp,255,'\0');
	{ 
		strncpy(str[count++],tmp,255);
		outFile<<tmp;
	}
	for(int i=0;i<count;i++)
		cout<<str[i]<<endl;
	inFile.close();
	getch();
while ((schet<count)){
	
	finalrezult=0.4;
	SumMvoice=0; SumResultmas=0;
	srav=0;
	 for (int i = 0; i < 128; i++){
                mvoice[i] = 0;
        }
	 
  //textBox2->Text = gcnew System::String(str[2]);
  int n = 0; 
    ifstream file(str[schet]); 
    while (file >> mvoice[n]) ++n; 
		file.close();
	//label1->Text=mvoice[1].ToString();
  
  for (int i=0; i<128; i++)
    {
      SumMvoice=SumMvoice+mvoice[i];
      SumResultmas=SumResultmas+rezultmas[i];
    }
  for (int i=0; i<128; i++)
    {
      srav=srav+abs(mvoice[i]/SumMvoice-rezultmas[i]/SumResultmas);
    }
  richTextBox1->Text=richTextBox1->Text+gcnew System::String(str[schet])+" "+srav.ToString()+"\n";
  if ((srav<0.36)&&(srav<finalrezult)) {
	  findv=true;
//label1->Text=srav.ToString();
	  finalrezult=srav;
      label1->Text= gcnew System::String(str[schet]);
  } 
 
    schet++;
 
		}
if (findv==false){label1->Text="Совпадений в базе не обнаружено";}
}
};
	


}

