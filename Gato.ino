#include "Servo.h"
#include "SimpleTimer.h"
#include "Ultrasonic.h"

SimpleTimer timer;

// Cabeça
Servo cabeca;
Servo pescoco;

// Dianteira
Servo pde;
Servo cde;
Servo pdd;
Servo cdd;

// Traseira
Servo pte;
Servo cte;
Servo ptd;
Servo ctd;

Servo servos[10] = { pescoco, pde, cde, pdd, cdd, pte, cte, ptd, ctd, cabeca };
int portasServos[10] = { 5, 12, 13, 8, 9, 10, 11, 6, 7, 4 };

int grauInicialServo = 90;

int grausPDE = grauInicialServo;
int grausCDE = grauInicialServo;

int grausPTD = grauInicialServo;
int grausCTD = grauInicialServo;

int grausPTE = grauInicialServo;
int grausCTE = grauInicialServo;

int grausPDD = grauInicialServo;
int grausCDD = grauInicialServo;

int grausPDEAtual = grauInicialServo;
int grausCDEAtual = grauInicialServo;

int grausPTDAtual = grauInicialServo;
int grausCTDAtual = grauInicialServo;

int grausPTEAtual = grauInicialServo;
int grausCTEAtual = grauInicialServo;

int grausPDDAtual = grauInicialServo;
int grausCDDAtual = grauInicialServo;

// Sensor Ultrasom da Cabeça

int pinoTrigger = 2;
int pinoEcho = 3;

unsigned long duracao;
unsigned long distancia;
bool objetoDetectado = false;
int distanciaNecessariaObstaculoCabeca = 10;
int quantidadeNecessariaDetectarObstaculo = 3;
int contadorObjetoDetectado = 0;
bool deteccaoObjetoLiberada = true;
int delayDetectarObstaculo = 300;

bool movimentarServos = true;

unsigned long tempoAtual;

unsigned long tempoRecebimentoSerial;
float delayRecebimentoSerial = 200;
String valorRecebidoCompleto;
bool resetado;

int passoAtualPDE = 0;
int passoAtualCDE = 0;
int passoAtualPTE = 0;
int passoAtualCTE = 0;
int passoAtualPDD = 0;
int passoAtualCDD = 0;
int passoAtualPTD = 0;
int passoAtualCTD = 0;

int qtdeMovimentos = 5;
int delayMov = 200;
long delayPassos = 0;

int movimentacaoPDE[] = { 80, 50, 50, 50, 80 };
int delayPDE[] = { delayMov, delayMov, delayMov, delayMov, delayMov };
int movimentacaoCDE[] = { 105, 65, 65, 65, 105 };
int delayCDE[] = { delayMov, delayMov, delayMov, delayMov, delayMov };

int movimentacaoPTE[] = { 90, 90, 110, 110, 90 };
int delayPTE[] = { delayMov, delayMov, delayMov, delayMov, delayMov };
int movimentacaoCTE[] = { 90, 90, 115, 80, 90 };
int delayCTE[] = { delayMov, delayMov, delayMov, delayMov, delayMov };

int movimentacaoPDD[] = { 130, 100, 100, 130, 130 };
int delayPDD[] = { delayMov, delayMov, delayMov, delayMov, delayMov };
int movimentacaoCDD[] = { 115, 65, 65, 115, 115 };
int delayCDD[] = { delayMov, delayMov, delayMov, delayMov, delayMov };

int movimentacaoPTD[] = { 70, 70, 90, 90, 90 };
int delayPTD[] = { delayMov, delayMov, delayMov, delayMov, delayMov };
int movimentacaoCTD[] = { 100, 90, 90, 90, 90 };
int delayCTD[] = { delayMov, delayMov, delayMov, delayMov, delayMov };

void setup() {
	Serial.begin(9600);

	pinMode(pinoTrigger, OUTPUT);
	pinMode(pinoEcho, INPUT);

	inicializarServos();

	timer.setTimeout(3000, iniciarMovimentoPata);

	timer.setTimeout(delayDetectarObstaculo, detectarObstaculoCabeca);
}

void detectarObstaculoCabeca() {
	// Clears the trigPin
	digitalWrite(pinoTrigger, LOW);
	delayMicroseconds(2);

	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(pinoTrigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinoTrigger, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
	duracao = pulseIn(pinoEcho, HIGH);

	// Calculating the distance
	distancia = duracao * 0.034 / 2;

	if (distancia < distanciaNecessariaObstaculoCabeca) {
		contadorObjetoDetectado++;
	}
	else {
		contadorObjetoDetectado = 0;
	}

	if (contadorObjetoDetectado >= quantidadeNecessariaDetectarObstaculo)
	{
		objetoDetectado = true;
	}
	else {
		objetoDetectado = false;
	}

	if (objetoDetectado && deteccaoObjetoLiberada) {
		deteccaoObjetoLiberada = false;

		movimentarServos = false;

		pescoco.write(0);
		delay(1000);
		pescoco.write(180);
		delay(1000);
		pescoco.write(90);
		delay(1000);
	}
	else if (!objetoDetectado && !deteccaoObjetoLiberada) {
		deteccaoObjetoLiberada = true;

		movimentarServos = true;
	}

	timer.setTimeout(delayDetectarObstaculo, detectarObstaculoCabeca);
}

void inicializarServos() {
	/*for (int i = 0; i < length(servos); i++)
	{
	  Servo servo = servos[i];
	  int portaServo = portasServos[i];
	  servo.attach(portaServo);
	  servo.write(grauInicialServo);
	}*/

	pescoco.attach(portasServos[0]);
	pde.attach(portasServos[1]);
	cde.attach(portasServos[2]);
	pdd.attach(portasServos[3]);
	cdd.attach(portasServos[4]);
	pte.attach(portasServos[5]);
	cte.attach(portasServos[6]);
	ptd.attach(portasServos[7]);
	ctd.attach(portasServos[8]);
	cabeca.attach(portasServos[9]);

	reiniciarServos();
}

void reiniciarServos() {
	Serial.println("reiniciarServos");

	pde.write(grauInicialServo);
	cde.write(grauInicialServo);
	ptd.write(grauInicialServo);
	ctd.write(grauInicialServo);
	pte.write(grauInicialServo);
	cte.write(grauInicialServo);
	pdd.write(grauInicialServo);
	cdd.write(grauInicialServo);
	cabeca.write(grauInicialServo);

	grausPDE = grauInicialServo;
	grausCDE = grauInicialServo;
	grausPTD = grauInicialServo;
	grausCTD = grauInicialServo;
	grausPTE = grauInicialServo;
	grausCTE = grauInicialServo;
	grausPDD = grauInicialServo;
	grausCDD = grauInicialServo;
}

void iniciarMovimentoPata() {
	movimentarPDE();
	movimentarCDE();
	movimentarPTE();
	movimentarCTE();
	movimentarPDD();
	movimentarCDD();
	movimentarPTD();
	movimentarCTD();
}

void movimentarPDE() {
	grausPDE = movimentacaoPDE[passoAtualPDE];

	int delay = delayPDE[passoAtualPDE];

	if (passoAtualPDE < qtdeMovimentos - 1) {
		passoAtualPDE++;
	}
	else {
		passoAtualPDE = 0;
	}

	timer.setTimeout(delay, movimentarPDE);
}

void movimentarCDE() {
	grausCDE = movimentacaoCDE[passoAtualCDE];

	int delay = delayCDE[passoAtualCDE];

	if (passoAtualCDE < qtdeMovimentos - 1) {
		passoAtualCDE++;
	}
	else {
		passoAtualCDE = 0;
	}

	timer.setTimeout(delay, movimentarCDE);
}

void movimentarPTE() {
	grausPTE = movimentacaoPTE[passoAtualPTE];

	int delay = delayPTE[passoAtualPTE];

	if (passoAtualPTE < qtdeMovimentos - 1) {
		passoAtualPTE++;
	}
	else {
		passoAtualPTE = 0;
	}

	timer.setTimeout(delay, movimentarPTE);
}

void movimentarCTE() {
	grausCTE = movimentacaoCTE[passoAtualCTE];

	int delay = delayCTE[passoAtualCTE];

	if (passoAtualCTE < qtdeMovimentos - 1) {
		passoAtualCTE++;
	}
	else {
		passoAtualCTE = 0;
	}

	timer.setTimeout(delay, movimentarCTE);
}

void movimentarPDD() {
	grausPDD = movimentacaoPDD[passoAtualPDD];

	int delay = delayPDD[passoAtualPDD];

	if (passoAtualPDD < qtdeMovimentos - 1) {
		passoAtualPDD++;
	}
	else {
		passoAtualPDD = 0;
	}

	timer.setTimeout(delay, movimentarPDD);
}

void movimentarCDD() {
	grausCDD = movimentacaoCDD[passoAtualCDD];

	int delay = delayCDD[passoAtualCDD];

	if (passoAtualCDD < qtdeMovimentos - 1) {
		passoAtualCDD++;
	}
	else {
		passoAtualCDD = 0;
	}

	timer.setTimeout(delay, movimentarCDD);
}

void movimentarPTD() {
	grausPTD = movimentacaoPTD[passoAtualPTD];

	int delay = delayPTD[passoAtualPTD];

	if (passoAtualPTD < qtdeMovimentos - 1) {
		passoAtualPTD++;
	}
	else {
		passoAtualPTD = 0;
	}

	timer.setTimeout(delay, movimentarPTD);
}

void movimentarCTD() {
	grausCTD = movimentacaoCTD[passoAtualCTD];

	int delay = delayCTD[passoAtualCTD];

	if (passoAtualCTD < qtdeMovimentos - 1) {
		passoAtualCTD++;
	}
	else {
		passoAtualCTD = 0;
	}

	timer.setTimeout(delay, movimentarCTD);
}

void atualizarServos() {
	atualizarServo(grausPDEAtual, grausPDE, pde);
	atualizarServo(grausCDEAtual, grausCDE, cde);
	atualizarServo(grausPTEAtual, grausPTE, pte);
	atualizarServo(grausCTEAtual, grausCTE, cte);
	atualizarServo(grausPDDAtual, grausPDD, pdd);
	atualizarServo(grausCDDAtual, grausCDD, cdd);
	atualizarServo(grausPTDAtual, grausPTD, ptd);
	atualizarServo(grausCTDAtual, grausCTD, ctd);
}

void atualizarServo(int& grausAtual, int graus, Servo& servo) {
	int passo = 1;
	int sentido;
	int intervalo;

	if (grausAtual > graus)
	{
		sentido = -1;
		intervalo = grausAtual - graus;
	}
	else {
		sentido = 1;
		intervalo = graus - grausAtual;
	}

	passo *= sentido;

	if (intervalo > 0) {
		grausAtual += sentido;
		//Serial.println(grausAtual);
		//grausAtual -= (grausAtual % sentido);
		servo.write(grausAtual);
		delay(3);
	}
}

void construirValorRecebido()
{
	if (Serial.available() > 0)
	{
		resetado = false;

		tempoRecebimentoSerial = tempoAtual;

		while (Serial.available() > 0)
		{
			char valorRecebido = Serial.read();

			valorRecebidoCompleto += valorRecebido;
		}
	}
	else if (!resetado && tempoAtual > tempoRecebimentoSerial + delayRecebimentoSerial)
	{
		processarValorRecebido();

		resetarValorRecebido();
	}
}

void resetarValorRecebido()
{
	valorRecebidoCompleto = "";

	resetado = true;
}

void processarValorRecebido()
{
	String valores[16];
	int chave = 0;

	char valorRecebidoCompletoArray[100];
	valorRecebidoCompleto.toCharArray(valorRecebidoCompletoArray, 100);

	char* separado = strtok(valorRecebidoCompletoArray, " ");

	while (separado != NULL)
	{
		valores[chave] = separado;

		chave++;

		separado = strtok(NULL, " ");
	}

	int size = sizeof(valores) / sizeof(valores[0]);

	for (int i = 0; i < size; i += 2) {
		String motor = valores[i];
		int graus = 0;

		if (valores[i + 1] != "")
		{
			graus = valores[i + 1].toInt();
		}

		processarMotor(motor, graus);
	}
}

void processarMotor(String motor, int graus) {
	if (motor == "") {
		return;
	}

	graus = constrain(graus, 0, 180);

	Serial.print("m: ");
	Serial.print(motor);
	Serial.print(", g: ");
	Serial.println(graus);

	if (motor == "pde")
	{
		grausPDE = graus;
	}
	else if (motor == "cde")
	{
		grausCDE = graus;
	}
	else if (motor == "pdd")
	{
		grausPDD = graus;
	}
	else if (motor == "cdd")
	{
		grausCDD = graus;
	}
	else if (motor == "pte")
	{
		grausPTE = graus;
	}
	else if (motor == "cte")
	{
		grausCTE = graus;
	}
	else if (motor == "ptd")
	{
		grausPTD = graus;
	}
	else if (motor == "ctd")
	{
		grausCTD = graus;
	}
	else if (motor == "reset")
	{
		reiniciarServos();
	}
}

void loop() {
	timer.run();

	tempoAtual = millis();

	construirValorRecebido();

	if (movimentarServos)
	{
		atualizarServos();
	}
}