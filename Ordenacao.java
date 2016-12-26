/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ordenacao;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author eduardo-pc
 */
public class Ordenacao {

    static final int quantidade = 1000;
   
    static Calendar cal;
    static long tempoInicial;
   

    public static void main(String[] args) throws IOException {
        
        Scanner teclado = new Scanner(System.in);
        Random rand = new Random();
        
        System.out.println("Digite o tamanho do vetor: ");
        int op = teclado.nextInt();
        
        int[] vetor = new int[op];
        int[] vetorCopia = new int[op];
        System.out.println();

        for (int i = 0; i < vetor.length; i++) {
            vetorCopia[i] = vetor[i] = rand.nextInt(quantidade) + 1;;
            //System.out.println(vetor[i]);
        }
        
        

        while (true) {
            System.out.println("\nEscolha uma opcao: ");
            System.out.println("1 - Bubble sort");
            System.out.println("2 - Insertion sort");
            System.out.println("3 - Selection sort");
            System.out.println("4 - Heap sort");
            System.out.println("5 - Quick sort");
            System.out.println("6 - Sair");
            op = teclado.nextInt();

                      
            tempoInicial = System.currentTimeMillis();          
            
            vetor = vetorCopia.clone();
                

            switch (op) {
                case 1:
                    bubbleSort(vetor);
                    break;
                case 2:
                    insertionSort(vetor);
                    break;
                case 3:
                     selectionSort(vetor);
                    break;
                case 4:
                    heapSort(vetor);
                    break;
                case 5:
                    quickSort(vetor,0,vetor.length-1);
                    exibir(vetor);
                    break;
                case 6:
                    return;
                default:
                    System.out.println("Opcao invalida\n");
                    break;
            }
            System.out.println();
        }
    }

    public static void insertionSort(int[] vetor) {
        int j, valor, i;
        
        for (j = 1; j < vetor.length; j++) {
            valor = vetor[j];            
            for (i = j - 1; (i >= 0) && (vetor[i] > valor); i--) {
                vetor[i + 1] = vetor[i];                               
            }
            vetor[i + 1] = valor;
        }
        exibir(vetor);
    }
    
    public static void bubbleSort(int vetor[]){
                 boolean troca = true;
                 int aux;
                 while (troca) {                   
                     troca = false;
                     for (int i = 0; i < vetor.length - 1; i++) {                                                
                         if (vetor[i] > vetor[i + 1]) {
                             aux = vetor[i];
                             vetor[i] = vetor[i + 1];
                             vetor[i + 1] = aux;
                             troca = true;                            
                         }
                     }
                 }
                 exibir(vetor);
         }
      
      public static void selectionSort(int[] vetor) {
   for (int fixo = 0; fixo < vetor.length - 1; fixo++) {      
     int menor = fixo;
   
     for (int i = menor + 1; i < vetor.length; i++) {                
        if (vetor[i] < vetor[menor]) {           
           menor = i;
        }
     }
     
     if (menor != fixo) {        
       int t = vetor[fixo];
       vetor[fixo] = vetor[menor];
       vetor[menor] = t;       
     }
   }
   exibir(vetor);
 }
    
//inicio do heapsort    
  public static void heapSort(int[] vetor) {
        construirMaxHeap(vetor);
        int n = vetor.length;
        for (int i = vetor.length - 1; i > 0; i--) {            
            troca(vetor, i, 0);
            maxHeap(vetor, 0, --n);
        }
        exibir(vetor);
    }

    private static void construirMaxHeap(int[] vetor) {
        for (int i = vetor.length / 2 - 1; i >= 0; i--)             
            maxHeap(vetor, i, vetor.length);   
    }

     private static void maxHeap(int[] vetor, int pos, int tamanhoDoVetor)  
     {  

         int max = 2 * pos + 1, direita = max + 1;  
         
         if (max < tamanhoDoVetor)  
         {             
             if (direita < tamanhoDoVetor && vetor[max] < vetor[direita]){  
                 
                 max = direita;
             }
             
             if (vetor[max] > vetor[pos])  
             {  
                 troca(vetor, max, pos);  
                 maxHeap(vetor, max, tamanhoDoVetor);  
             }  
         }  
     }

    public static void troca(int[] vetor, int j, int aposJ) {
        int aux = vetor[j];
        vetor[j] = vetor[aposJ];
        vetor[aposJ] = aux;       
    }
//fim do heapsort
      
    
//inicio quicksort    
         public static void quickSort(int[] vetor, int inicio, int fim) {            
               if (inicio < fim) {             
                      int posPivo = separar(vetor, inicio, fim);
                      quickSort(vetor, inicio, posPivo - 1);
                      quickSort(vetor, posPivo + 1, fim);                      
               }               
         }
   
         public static int separar(int[] vetor, int inicio, int fim) {
               int pivo = vetor[inicio];
               int i = inicio + 1, f = fim;              
               while (i <= f) {                 
                      if (vetor[i] <= pivo){
                             i++;
                      }                      
                      else if (pivo < vetor[f]){
                          
                             f--;}
                      else {   
                             int troca = vetor[i];
                             vetor[i] = vetor[f];
                             vetor[f] = troca;
                             i++;
                             f--;
                      }
               }
               vetor[inicio] = vetor[f];
               
               vetor[f] = pivo;
               return f;
         }
//fim quicksort    
    
    public static void exibir(int[] vetor) {

        
        long tempoFinal = System.currentTimeMillis();
        System.out.println("Diferença = " + (tempoFinal - tempoInicial) + " ms");
        /*for (int i = 0; i < vetor.length; i++) {
            System.out.println(vetor[i]);
        }*/
        
    }

}
