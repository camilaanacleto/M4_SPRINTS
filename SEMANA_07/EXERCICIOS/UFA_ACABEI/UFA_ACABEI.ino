#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
/* INCLUDE ESP2SOTA LIBRARY */
#include <ESP2SOTA.h>
#define buzzer 37

const char* ssid = "Camii";
const char* password = "123456789abc";

WebServer server(80);

String HTML(){

String cd = "<!DOCTYPE html>";
cd += "<html lang=\"en\">";
cd += "<head>";
cd += "<meta charset=\"UTF-8\">";
cd += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
cd += "<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";
cd += "<title>JOGO DA CAMISSS</title>";
cd += "<style>";
cd += "*, *::before, *::after {";
cd += "box-sizing: border-box;";
cd += "font-family: Gotham Rounded;";
cd += "}";
cd += ":root {";
cd += "--hue-neutral: 200;";
cd += "--hue-wrong: 0;";
cd += "--hue-correct: 145;";
cd += "}";
cd += "body {";
cd += "--hue: var(--hue-neutral);";
cd += "padding: 0;";
cd += "margin: 0;";
cd += "display: flex;";
cd += "width: 100vw;";
cd += "height: 100vh;";
cd += "justify-content: center;";
cd += "align-items: center;";
cd += "background-color: rgb(232, 113, 177);";
cd += "}";
cd += "body.correct {";
cd += "--hue: var(--hue-correct);";
cd += "}";
cd += "body.wrong {";
cd += "--hue: var(--hue-wrong);";
cd += "}";
cd += ".container {";
cd += "width: 800px;";
cd += "max-width: 80%;";
cd += "background-color: white;";
cd += "border-radius: 5px;";
cd += "padding: 10px;";
cd += "box-shadow: 0 0 10px 2px;";
cd += "}";
cd += ".btn-grid {";
cd += "display: grid;";
cd += "grid-template-columns: repeat(2, auto);";
cd += "gap: 10px;";
cd += "margin: 20px 0;";
cd += "}";
cd += ".btn {";
cd += "--hue: var(--hue-neutral);";
cd += "border: 1px solid hsl(var(--hue), 100%, 30%);";
cd += "background-color: hsl(var(--hue), 100%, 50%);";
cd += "border-radius: 5px;";
cd += "padding: 5px 10px;";
cd += "color: white;";
cd += "outline: none;";
cd += "}";
cd += ".btn:hover {";
cd += "border-color: black;";
cd += "}";
cd += ".btn.correct {";
cd += "--hue: var(--hue-correct);";
cd += "color: black;";
cd += "}";
cd += ".btn.wrong {";
cd += "--hue: var(--hue-wrong);";
cd += "}";
cd += ".start-btn, .next-btn {";
cd += "font-size: 1.5rem;";
cd += "font-weight: bold;";
cd += "padding: 10px 20px;";
cd += "}";
cd += ".controls {";
cd += "display: flex;";
cd += "justify-content: center;";
cd += "align-items: center;";
cd += "}";
cd += ".hide {";
cd += "display: none;";
cd += "}";
cd += "</style>";
cd += "</head>";
cd += "<body>";
cd += "<div class=\"container\">";
cd += "<div id=\"question-container\" class=\"hide\">";
cd += "<div id=\"question\">Question</div>";
cd += "<div id=\"answer-buttons\" class=\"btn-grid\">";
cd += "  <button class=\"btn\">Answer 1</button>";
cd += "  <button class=\"btn\">Answer 2</button>";
cd += "  <button class=\"btn\">Answer 3</button>";
cd += "  <button class=\"btn\">Answer 4</button>";
cd += "</div>";
cd += "</div>";
cd += "<div class=\"controls\">";
cd += "<button id=\"start-btn\" class=\"start-btn btn\">COMEÇAR O JOGO DA CAMISSS</button>";
cd += "<button id=\"next-btn\" class=\"next-btn btn hide\">Próximo</button>";
cd += "</div>";
cd += "</div>";
cd += "<script>";
cd += "const startButton = document.getElementById('start-btn');";
cd += "const nextButton = document.getElementById('next-btn');";
cd += "const questionContainerElement = document.getElementById('question-container');";
cd += "const questionElement = document.getElementById('question');";
cd += "const answerButtonsElement = document.getElementById('answer-buttons');";
cd += "let shuffledQuestions, currentQuestionIndex;";
cd += "startButton.addEventListener('click', startGame);";
cd += "nextButton.addEventListener('click', () => {";
cd += "currentQuestionIndex++;";
cd += "setNextQuestion();";
cd += "});";
cd += "function startGame() {";
cd += "console.log('o caze eh muito lindo');";
cd += "startButton.classList.add('hide');";
cd += "shuffledQuestions = questions.sort(() => Math.random() - .5);";
cd += "currentQuestionIndex = 0;";
cd += "questionContainerElement.classList.remove('hide');";
cd += "setNextQuestion()";
cd += "}";
cd += "function setNextQuestion() {";
cd += "resetState();";
cd += "showQuestion(shuffledQuestions[currentQuestionIndex])";
cd += "}";
cd += "function showQuestion(question) {";
cd += "questionElement.innerText = question.question;";
cd += "question.answers.forEach(answer => {";
cd += "const button = document.createElement('button');";
cd += "button.innerText = answer.text;";
cd += "button.classList.add('btn');";
cd += "if (answer.correct) {";
cd += "button.dataset.correct = answer.correct";
cd += "}";
cd += "button.addEventListener('click', selectAnswer);";
cd += "answerButtonsElement.appendChild(button)";
cd += "})";
cd += "}";
cd += "function resetState() {";
cd += "clearStatusClass(document.body);";
cd += "nextButton.classList.add('hide');";
cd += "while (answerButtonsElement.firstChild) {";
cd += "answerButtonsElement.removeChild(answerButtonsElement.firstChild)";
cd += "}";
cd += "}";
cd += "function selectAnswer(e) {";
cd += "const selectedButton = e.target;";
cd += "const correct = selectedButton.dataset.correct;";
cd += "setStatusClass(document.body, correct);";
cd += "Array.from(answerButtonsElement.children).forEach(button => {";
cd += "setStatusClass(button, button.dataset.correct)";
cd += "});";
cd += "if (shuffledQuestions.length > currentQuestionIndex + 1) {";
cd += "nextButton.classList.remove('hide')";
cd += "} else {";
cd += "startButton.innerText = 'Começar de Novo';";
cd += "startButton.classList.remove('hide')";
cd += "}";
cd += "}";
cd += "function setStatusClass(element, correct) {";
cd += "clearStatusClass(element);";
cd += "if (correct) {";
cd += "element.classList.add('correct');";
cd += "} else {";
cd += "element.classList.add('wrong')";
cd += "}";
cd += "}";
cd += "function clearStatusClass(element) {";
cd += "element.classList.remove('correct');";
cd += "element.classList.remove('wrong')";
cd += "}";
cd += "const questions = [";
cd += "{";
cd += "question: 'Qual é o melhor professor de programação da vida?',";
cd += "answers: [";
cd += "{ text: 'Leonardo', correct: true },";
cd += "{ text: 'Fausto Silva', correct: false }";
cd += "]";
cd += "},";
cd += "{";
cd += "question: 'Quanto é 2 elevado a 0?',";
cd += "answers: [";
cd += "{ text: '1', correct: true },";
cd += "{ text: '52', correct: false },";
cd += "{ text: '0', correct: false },";
cd += "{ text: '2', correct: false }";
cd += "]";
cd += "},";
cd += "{";
cd += "question: 'Qual é o melhor curso do Inteli?',";
cd += "answers: [";
cd += "{ text: 'Ciência da Computação', correct: false },";
cd += "{ text: 'Sistemas de Informação', correct: true },";
cd += "{ text: 'Engenharia de Computação', correct: false },";
cd += "{ text: 'Engenharia de Software', correct: false }";
cd += "]";
cd += "},";
cd += "{";
cd += "question: 'O professor deve me dar 10?',";
cd += "answers: [";
cd += "{ text: 'NÃO', correct: false },";
cd += "{ text: 'SIM', correct: true }";
cd += "]";
cd += "}";
cd += "]";
cd += "</script>";
cd += "</body>";
cd += "</html>";
return cd;
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid, password);
  delay(1000);
  IPAddress IP = IPAddress (10, 10, 10, 1);
  IPAddress NMask = IPAddress (255, 255, 255, 0);
  WiFi.softAPConfig(IP, IP, NMask);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  /* SETUP YOR WEB OWN ENTRY POINTS */
  server.on("/game", HTTP_GET, []() {
    tone(buzzer,700,3000);
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", HTML());
  });

  server.on("/myurl", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", "Hello there!");
  });

  /* INITIALIZE ESP2SOTA LIBRARY */
  ESP2SOTA.begin(&server);
  server.begin();
}

void loop(void) {
  /* HANDLE UPDATE REQUESTS */
  server.handleClient();

  /* YOUR LOOP CODE HERE */


  
  delay(5);
}