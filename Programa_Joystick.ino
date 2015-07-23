int Filas[8] = {13,4,5,16,7,15,11,10}; //asignación de pines correspondientes a cada fila, en orden ascendente
int Columnas[8] = {6,3,8,2,14,9,12,17}; //asignación de pines correspondientes a cada columna, en orden ascendente
int ColumnaActual=3; //Declaración de columna inicial
int FilaActual=3; //Declaración de fila inicial
int Xreposo; //Variable que se utilizará para guardar el valor del eje X en reposo
int Yreposo; //Variable que se utilizará para guardar el valor del eje Y en reposo
//el primer valor de los vectores se encuentra en la posicion 0 de cada uno, por lo cual para referirse a una fila o columna dentro del vector, se toma un numero menor  a la
// fila o columna; ejemplo: para la fila 4, el valor es Filas[3].
void setup()
   {   
        for (int j=2; j<19; j++) //Declaración de los pines de salida correspondientes a cada led
        {
        pinMode(j, OUTPUT);
        }
        ApagarTodo(); //Apagar todos los leds
        Yreposo = analogRead(A5); //lectura del valor de reposo del joystick en el eje Y
        Xreposo = analogRead(A4); //lectura del valor de reposo del joystick en el eje X
        EncenderFila(3); //Encendender la fila inicial
        EncenderColumna(3); //Encender la columna inicial
        EncenderFila(4); //Encender la fila siguiente
        EncenderColumna(4); //Encender la columna siguiente para conseguir un cuadrado
   }

   //Siempre se encenderá un cuadrado de 2x2, por lo cual la fila y columna actual se tomará como referencia para encender todo el cuadrado
   //La primer fila/columna será la que se guarda en las variables FilaActual y ColumnaActual, y la siguiente será la posición siguiente
   //En el eje correspondiente; ejemplo: FilaActual = 4, se encienden las filas 4 y 5(lo mismo para las columnas)
   //El valor de la fila actual es el número real en la matriz, por lo que será necesario leer una posición menos en el vector.

void ApagarTodo() //Funcion que apaga todos los leds
{
          for(int p=0;p<8;p++)
        {
          digitalWrite(Filas[p],HIGH); //Las filas se apagan enviado una señal HIGH
          digitalWrite(Columnas[p],LOW); //Las columnas se apagan enviando una señal LOW
        }
}


void loop()
   {
              
              int y= analogRead(A5); //Lectura del valor actual de Y
              int x= analogRead(A4); //Lectura del valor actual de X
              ApagarTodo(); //Apagar todos los leds
              if(y > Yreposo+1) //Si el nuevo valor de Y es mayor al de reposo
              {
                if(FilaActual <=5) //Y la fila actual no es la anteultima(si se avanza mas se sale de la matriz led)
                {
                EncenderFila(FilaActual+2); //Encender la fila siguiente
                delay(100);
                ApagarColumna(FilaActual); //Apagar la fila actual
                FilaActual = FilaActual + 1; //Incrementar la fila actual a la nueva posición
                }
                else //Si la fila es la anteultima
                {
                  EncenderFila(0); //Encender la primer fila
                  EncenderFila(7); //Encender la ultima fila
                  delay(100);
                  ApagarColumna(6); //Apagar la fila actual
                  FilaActual = 7; //Asignar la fila actual a la nueva posicion
                }
              }
              else //si el nuevo valor de Y no es mayor al de reposo
              {
                if(y < Yreposo-1) //si el nuevo valor de Y es menor al de reposo
                {
                  if(FilaActual>=1) //y la fila actual es mayor o igual a la segunda
                  {
                      EncenderFila(FilaActual-1); //Encender la fila anterior
                      delay(100);
                      ApagarColumna(FilaActual+1); //Apagar la columna Actual
                      FilaActual = FilaActual - 1; //Asignar la fila actual a la nueva posición
                  }
                  else //si la fila actual es la primera
                  {
                      EncenderFila(7); //Encender la ultima fila
                      EncenderFila(0); //Encender la primer fila
                      delay(100);
                      ApagarColumna(1); //Apagar la segunda fila
                      FilaActual = 7; //Asignar la fila actual a la nueva posición
                  }
                }
                else //Se repite todo para el eje X
                {
                   if(x > Xreposo+1)
                    {
                        if(ColumnaActual<=5)
                          {
                              EncenderColumna(ColumnaActual+2);
                              delay(100);
                              ApagarFila(ColumnaActual);
                              ColumnaActual = ColumnaActual + 1;
                          }
                          else
                          {
                              EncenderColumna(0);
                              EncenderColumna(7);
                              delay(100);
                              ApagarFila(6);
                              ColumnaActual = 0;
                          }
                      }
                      else
                      {
                          if( x < Xreposo-1)
                          {
                              if(ColumnaActual>=1)
                              {
                                  EncenderColumna(ColumnaActual-1);
                                  delay(100);
                                  ApagarFila(ColumnaActual+1);
                                  ColumnaActual = ColumnaActual - 1;
                              }
                              else
                              {
                                  EncenderColumna(7);
                                  EncenderColumna(0);
                                  delay(100);
                                  ApagarFila(1);
                                  ColumnaActual = 7;
                              }
                          }
                        }
                  }
                }
   
              while((x == Xreposo && x == Xreposo)  && (y == Yreposo && y == Yreposo)) //Mientras el joystick este en reposo, encender la fila y columna actual y seguir leyendo los valores de entrada hasta que cambien
              {
                ApagarColumna(ColumnaActual);
                ApagarColumna(ColumnaActual+1);
                ApagarFila(FilaActual+1);
                ApagarFila(FilaActual);
                delay(200);
                EncenderColumna(ColumnaActual);
                EncenderColumna(ColumnaActual +1);
                EncenderFila(FilaActual);
                EncenderFila(FilaActual + 1);
                y= analogRead(A5);
                x= analogRead(A4);
              }
   }

    
    
   void EncenderFila(int fila)
   {
        
        digitalWrite(Filas[fila],HIGH);
        
   }

   void EncenderColumna(int col)
   {
        digitalWrite(Columnas[col],LOW);
        
   }

      void ApagarFila(int fila)
   {
        
        digitalWrite(Filas[fila],LOW);
        
   }

   void ApagarColumna(int col)
   {
        digitalWrite(Columnas[col],HIGH);

   }

