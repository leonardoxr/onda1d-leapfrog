#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


void atualizar_onda(double u_new[],double u_now[],double u_old[],int jmax,double k);

void main()
{

    FILE *arq;
    arq = fopen("erro.txt", "w+");

    int tmax,i,j,jmax;
    jmax = 50;
    double u_new[jmax],t,u_old[jmax],u_now[jmax],k,erro;

    tmax = 10;




    //k = 0.01;
    int n=1;
    while( n < 1000)
    {
        k = 0.001*n;

        for (j = 0 ; j < jmax ; j++)
        {
            u_now[j] = sin(M_PI*j/(jmax - 1));
        }

        for (j = 1; j< jmax-1 ; j++)
        {
            u_old[j] = u_now[j] + 0.5 * pow(k,2) * (u_now[j+1] - 2 * u_now[j] + u_now[j-1]);
        }




        for(t = 0 ; t < tmax ; t+=k)
        {
            if(t+k >tmax)
            {
                k = tmax -t;
            }
            atualizar_onda(u_new,u_now,u_old,jmax,k);

            memcpy(u_old,u_now, sizeof(double)*jmax);
            memcpy(u_now,u_new, sizeof(double)*jmax);
        }
        //printf("%lf\n", t);

        erro = 0;
        for(j = 0 ; j < jmax ; j++)
        {
            double analitica = cos((M_PI*t)/(jmax - 1))*sin((M_PI*j)/(jmax - 1));
            erro += fabs(analitica - u_now[j]);
        }
        erro = (erro/jmax);
        fprintf(arq,"%.12lf %.12lf\n", (n*0.001),(erro));




        n++;

    }

    fclose(arq);

}


void atualizar_onda(double u_new_[],double u_now_[],double u_old_[],int jmax,double k)
{
    int j;


    u_new_[0] = 0;
    u_new_[jmax-1] = 0;

    for(j = 1 ; j < jmax-1 ; j++)
    {
        u_new_[j] =   2 * u_now_[j] - u_old_[j] + pow(k,2) *( u_now_[j+1] - 2 * u_now_[j] + u_now_[j-1] );
    }







}
