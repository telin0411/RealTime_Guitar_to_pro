#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include <string.h>
//void pitch(int freq, int i);



int main()
{
	FILE *fin, *fout;
	fin = fopen("noteinfo.txt","r");
	fout = fopen("star2.txt", "w+t");

	double freq[200];
	int count = 0;
	int tmp;
	float song_tempo = 4;//這首歌的節拍 
	int input[80];
	int tempo = 0;
		
	while(fscanf(fin,"%d", &tmp)!=EOF)
	{
		input[count] = tmp;
		count = count+1;
	}
	
	int in_array[2][count/2];
	for(int i = 0;i<=1;i++)
	{
		for(int j = 0;j<=count/2-1;j++)
		{
			in_array[i][j] = input[i*count/2+j];
		}
	}
	
	/////////////////////////////////////////////////
	
	fprintf(fout,"     ");//一開始的空白 
    float count_for_bar=0;//計算是否一小節了 
    float in_array_f=0;
    int record_for_j=0;
	for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"Q");
                fprintf(fout,"    ");
                break;
            case 8:
                fprintf(fout,"E");
                fprintf(fout,"  ");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"   ");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout," \n");
        }
    }
	
	/////////////////////////////////////////////////
    	
	count_for_bar=0;
	fprintf(fout,"E||--");
    for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[1][j])
        {
            case 329:
                fprintf(fout,"0");
                break;
            case 349:
                fprintf(fout,"1");
                break;
            case 392:
                fprintf(fout,"3");
                break;
            case 440:
                fprintf(fout,"5");
                break;
            default:
                fprintf(fout,"-");
        }
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"----");
                break;
            case 8:
                fprintf(fout,"--");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"|--");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout,"|\n");
        }
    }
    
	/////////////////////////////////////////////////
    
	count_for_bar=0;
	fprintf(fout,"B||--");
    for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[1][j])
        {
            case 261:
                fprintf(fout,"1");
                break;
            case 293:
                fprintf(fout,"3");
                break;
            default:
                fprintf(fout,"-");
        }
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"----");
                break;
            case 8:
                fprintf(fout,"--");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"|--");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout,"|\n");
        }
    }
    
	/////////////////////////////////////////////////
    
    count_for_bar=0;
	fprintf(fout,"G||--");
    for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[1][j])
        {
            default:
                fprintf(fout,"-");
        }
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"----");
                break;
            case 8:
                fprintf(fout,"--");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"|--");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout,"|\n");
        }
    }
    
	/////////////////////////////////////////////////
    
    count_for_bar=0;
	fprintf(fout,"D||--");
    for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[1][j])
        {
            default:
                fprintf(fout,"-");
        }
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"----");
                break;
            case 8:
                fprintf(fout,"--");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"|--");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout,"|\n");
        }
    }
    
	/////////////////////////////////////////////////
    
    count_for_bar=0;
	fprintf(fout,"A||--");
    for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[1][j])
        {
            default:
                fprintf(fout,"-");
        }
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"----");
                break;
            case 8:
                fprintf(fout,"--");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"|--");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout,"|\n");
        }
    }
    
	/////////////////////////////////////////////////
    
    count_for_bar=0;
	fprintf(fout,"E||--");
    for(int j=0;count_for_bar<song_tempo/2;j++)
	{
        switch(in_array[1][j])
        {
            default:
                fprintf(fout,"-");
        }
        switch(in_array[0][j])
        {
            case 4:
                fprintf(fout,"----");
                break;
            case 8:
                fprintf(fout,"--");
                break;
        }
        in_array_f=in_array[0][j];
        count_for_bar=count_for_bar+1/in_array_f;
        if(count_for_bar==song_tempo/4)
        {
            fprintf(fout,"|--");
        }
        else if(count_for_bar==song_tempo/2)
        {
            fprintf(fout,"|\n");
        }
        record_for_j=j;
    }
    fprintf(fout,"\n\n");
	/////////////////////////////////////////////////
    
    while(record_for_j<count/2-1)
    {
    
        count_for_bar=0;
        fprintf(fout,"  ");//一開始的空白 
    	for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"Q");
                    fprintf(fout,"    ");
                    break;
                case 8:
                    fprintf(fout,"E");
                    fprintf(fout,"  ");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"   ");
            }
            else if(count_for_bar==song_tempo/2)
            {
                fprintf(fout," \n");
            }
        }
    	
    	/////////////////////////////////////////////////
        
    	count_for_bar=0;
    	fprintf(fout,"--");
        for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[1][j])
            {
                case 329:
                    fprintf(fout,"0");
                    break;
                case 349:
                    fprintf(fout,"1");
                    break;
                case 392:
                    fprintf(fout,"3");
                    break;
                case 440:
                    fprintf(fout,"5");
                    break;
                default:
                    fprintf(fout,"-");
            }
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"----");
                    break;
                case 8:
                    fprintf(fout,"--");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"|--");
            }
            else if(count_for_bar==song_tempo/2)
            {
                if(j==count/2-1)
                {
                    fprintf(fout,"||\n");
                }
                else
                {
                    fprintf(fout,"|\n");
                }
            }
        }
    	
    	/////////////////////////////////////////////////
        
    	count_for_bar=0;
    	fprintf(fout,"--");
        for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[1][j])
            {
                case 261:
                    fprintf(fout,"1");
                    break;
                case 293:
                    fprintf(fout,"3");
                    break;
                default:
                    fprintf(fout,"-");
            }
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"----");
                    break;
                case 8:
                    fprintf(fout,"--");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"|--");
            }
            else if(count_for_bar==song_tempo/2)
            {
                if(j==count/2-1)
                {
                    fprintf(fout,"||\n");
                }
                else
                {
                    fprintf(fout,"|\n");
                }
            }
        }
        
    	/////////////////////////////////////////////////
        
        count_for_bar=0;
    	fprintf(fout,"--");
        for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[1][j])
            {
                default:
                    fprintf(fout,"-");
            }
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"----");
                    break;
                case 8:
                    fprintf(fout,"--");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"|--");
            }
            else if(count_for_bar==song_tempo/2)
            {
                if(j==count/2-1)
                {
                    fprintf(fout,"||\n");
                }
                else
                {
                    fprintf(fout,"|\n");
                }
            }
        }
        
    	/////////////////////////////////////////////////
        
        count_for_bar=0;
    	fprintf(fout,"--");
        for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[1][j])
            {
                default:
                    fprintf(fout,"-");
            }
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"----");
                    break;
                case 8:
                    fprintf(fout,"--");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"|--");
            }
            else if(count_for_bar==song_tempo/2)
            {
                if(j==count/2-1)
                {
                    fprintf(fout,"||\n");
                }
                else
                {
                    fprintf(fout,"|\n");
                }
            }
        }
        
    	/////////////////////////////////////////////////
        
        count_for_bar=0;
    	fprintf(fout,"--");
        for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[1][j])
            {
                default:
                    fprintf(fout,"-");
            }
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"----");
                    break;
                case 8:
                    fprintf(fout,"--");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"|--");
            }
            else if(count_for_bar==song_tempo/2)
            {
                if(j==count/2-1)
                {
                    fprintf(fout,"||\n");
                }
                else
                {
                    fprintf(fout,"|\n");
                }
            }
        }
        
    	/////////////////////////////////////////////////
        
        count_for_bar=0;
    	fprintf(fout,"--");
        for(int j=record_for_j+1;count_for_bar<song_tempo/2;j++)
    	{
            switch(in_array[1][j])
            {
                default:
                    fprintf(fout,"-");
            }
            switch(in_array[0][j])
            {
                case 4:
                    fprintf(fout,"----");
                    break;
                case 8:
                    fprintf(fout,"--");
                    break;
            }
            in_array_f=in_array[0][j];
            count_for_bar=count_for_bar+1/in_array_f;
            if(count_for_bar==song_tempo/4)
            {
                fprintf(fout,"|--");
            }
            else if(count_for_bar==song_tempo/2)
            {
                if(j==count/2-1)
                {
                    fprintf(fout,"||\n");
                }
                else
                {
                    fprintf(fout,"|\n");
                }
            }
            record_for_j=j;
        }
        fprintf(fout,"\n\n");
        
        
    }

	
	/*
	for(int i = 0;i<=count/2-1;i++)
	{
		tempo = 1/in_array[0][i] + tempo;
		if(tempo == song_tempo)
		{
			pitch(in_array);
			tempo = 0;
		} 
	}
	*/
	
	
	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}

/*
void pitch(int in_array[2][count/2]);
{
	

}
*/
