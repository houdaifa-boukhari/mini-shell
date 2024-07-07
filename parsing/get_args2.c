#include "min.h"


/// cat "t't""y"'b'
char *whithout_q(char *str)
{
    char *re;
    if(!str)
        return NULL;
    int x =0;
    int q =0;
    char qq;
    int c =0;
    while (str[x])
    {
        
        if(str[x]== '"'||str[x]== '\'')
        {
            if(str[x]=='"' && q==0)
            {
                qq= '"';
                q++;
                // x++;
            
            }
            else if (str[x]=='\'' && q==0)
            {
                qq= '\'';
                q++;
                // x++;
            }
            else if(q !=0 && str[x]==qq)
            {

                q =0;
                // x++;

            }
            else
                c++;

            
        }
        else
            c++;
        
            x++; 
        
    }

    re =malloc(c+1);
    // printf("%d\n",c);
    x =0;
    q=0;
    qq='\0';
    c =0;

    while (str[x])
    {
        // printf("d\n");
        if(str[x]== '"'||str[x]== '\'')
        {
            if(str[x]=='"' && q==0)
            {
                qq= '"';
                q++;
                // x++;
            
            }
            else if (str[x]=='\'' && q==0)
            {
                qq= '\'';
                q++;
                // x++;
            }
            else if(q !=0 && str[x]==qq)
            {

                q =0;
                // x++;

            }
            else
                re[c++]=str[x];

            
        }
        else
            re[c++]=str[x];
        
        x++;
       
        
        
    }
    re[c]='\0';
    

    return re;
}

// char *get_cmd2(char **str)
// {
//     char *re;
//     int x =0;
//     if(!str||!str[0])
//         return NULL;
//     if(ft_strncmp(str[0],"<",2)==0||ft_strncmp(str[0],">",2)==0||ft_strncmp(str[0],"<<",3)==0||ft_strncmp(str[0],">>",3)==0)
//     {
//         while (str[x])
//         {
//             // printf("s=%s\n",str[x]);
//             if((ft_strncmp(str[x],"<",2)==0||ft_strncmp(str[x],">",2)==0||ft_strncmp(str[x],"<<",3)==0||ft_strncmp(str[x],">>",3)==0))
//                 x++;
//             else 
//                 break;
//             x++;
//         }
        

//         if(str[x] )
//             re =whithout_q(str[x]);
//         else
//             return NULL;
//     }
//     else
//         re = whithout_q(str[0]);


//     return re;
// }




// char **get_flags2(char **str)
// {
//     char **re;
//     int i =3;
//     int c =0;
//     if(!str||!str[0])
//         return NULL;

//     if(ft_strncmp(str[0],"<",2)==0||ft_strncmp(str[0],">",2)==0||ft_strncmp(str[0],"<<",3)==0||ft_strncmp(str[0],">>",3)==0)
//     {
//         i=3;
//         // printf("%s\n",str[i] ? str[i]:"(null)");
//         if( ft_tostrlen(str)<=i)
//             return NULL;
//         while (str[i])
//         {
//         // printf("ff\n");
//             if(str[i][1]&& str[i][1]=='-'&&(str[i][0]=='"' ||str[i][0]=='\''))
//                 c++;
//             else if(str[i][0]=='-')
//                 c++;
//             i++;
//         }
            
//     }
//     else
//     {
//         i = 1;
//         while (str[i])
//         {
//             if(str[i][1]&& str[i][1]=='-'&&(str[i][0]=='"' ||str[i][0]=='\''))
//                 c++;
//             else if(str[i][0]=='-')
//                 c++;
//             i++;
//         }

//     }
//     // printf("%d\n",c);


//     re = (char **)malloc((1 + c) * sizeof(char *));
//     i =0;
//     c =0;

//     // while (x<c)
//     // {
//     //     printf("%s\n",str[0]);
//     if(ft_strncmp(str[0],"<",2)==0||ft_strncmp(str[0],">",2)==0||ft_strncmp(str[0],"<<",3)==0||ft_strncmp(str[0],">>",3)==0)
//     {
//         i=3;
//         while (str[i])
//         {
//             if(str[i][1]&& str[i][1]=='-'&&(str[i][0]=='"' ||str[i][0]=='\''))
//                 re[c++]=whithout_q(str[i]);
//             else if(str[i][0]=='-')
//                 re[c++]=whithout_q(str[i]);
//             i++;
//         }
            
//     }
//     else
//     {
//         i = 1;
//         while (str[i])
//         {
//             // printf("i==%d\n",i);
//             //  printf("%s\n",str[i]);
//             if(str[i][1]&& str[i][1]=='-'&&(str[i][0]=='"' ||str[i][0]=='\''))
//             {
//                 re[c++]=whithout_q(str[i]);
//             }
//             else if(str[i][0]=='-')
//             {
                
//                 re[c++]=whithout_q(str[i]);
//             }
//             i++;
//         }

//     }
       
//     // }
    

//     re[c]=NULL;
    
    


//     return re;
// }



char **get_args(char **str)
{
    char **re;
    int x =0; 
    int c =0;
    while (str[x])
    {
        if(ft_strncmp(str[x],"<",2)==0||ft_strncmp(str[x],">",2)==0||ft_strncmp(str[x],"<<",3)==0||ft_strncmp(str[x],">>",3)==0)
        {
            x++;
        }
        else
            c++;
        x++;
        // c++;
    }
    re = (char **)malloc((c +1)*sizeof(char *));
    // printf("%d\n",c);
    x =0;
    c =0;
    while (str[x])
    {
        if(ft_strncmp(str[x],"<",2)==0||ft_strncmp(str[x],">",2)==0||ft_strncmp(str[x],"<<",3)==0||ft_strncmp(str[x],">>",3)==0)
        {
            x++;
        }
        else
            re[c++]=whithout_q( str[x]);
        x++;
        // c++;
    }
    re[c]=NULL;



    return re;
}



t_out *get_out(char **str)
{
    t_out *out;
    int x =0;
    int c =0;
    while (str[x])
    {
        if(!ft_strncmp(str[x],">",2)||!ft_strncmp(str[x],">>",3))
            c++;
        x++;
    }
    // printf("%d\n",c);
    out = malloc((c+1)*sizeof(t_out));
    c=0;
    x =0;
    while (str[x])
    {
        if(!ft_strncmp(str[x],">",2)||!ft_strncmp(str[x],">>",3))
        {
            if(!ft_strncmp(str[x],">",2))
            {
                out[c].out= whithout_q( str[x+1]);
                out[c].is_a=false;
                c++;
                // printf("ss %s\n",str[x+1]);

            }
            else
            {
                out[c].out= whithout_q(str[x+1]);
                out[c++].is_a=true; 
                // printf("ss %s\n",str[x+1]);               
            }
        }
        x++;
    }
    out[c].out= NULL;
    out[c++].is_a=false; 
    


    return out;

}

t_inp *get_inp(char **str)
{
    t_inp *inp;
    int x =0;
    int c =0;
    while (str[x])
    {
        if(!ft_strncmp(str[x],"<",2)||!ft_strncmp(str[x],"<<",3))
            c++;
        x++;
    }
    // printf("%d\n",c);
    inp = malloc((c+1)*sizeof(t_inp));
    c=0;
    x =0;
    while (str[x])
    {
        if(!ft_strncmp(str[x],"<",2)||!ft_strncmp(str[x],"<<",3))
        {
            if(!ft_strncmp(str[x],"<",2))
            {
                inp[c].inp=whithout_q(str[x+1]);
                inp[c].is_h=false;
                c++;
                // printf("ss %s\n",str[x+1]);

            }
            else
            {
                inp[c].inp=whithout_q(str[x+1]);

                inp[c++].is_h=true; 
                // printf("ss %s\n",str[x+1]);               
            }
        }
        x++;
    }
    inp[c].inp=NULL;
    inp[c].is_h=false;
    


    return inp;

}





// int main()
// {
//     char *str0 ="ls \"\" -a \"\" -l";
//     char *str1 ="l\"s\"> \"hello  <'worde\"  \"-l -a\" \"\">\"\" 'out'";
//     char *str2 ="l\"s\"< 'hello  \">> worde'  \"-l -a\">> out >f";
//     char *str3 ="<'cat'\"<\" \" min '2\" \"-e\"";

//     char *str4 = "'ca't file >out >>out1<< stop out2 > out3 \"-e\" -l";
//     char *str5 ="ls";
//     printf("%s\n",str5);
// //    printf("%s\n", set_speece(str3));
// char ** str =split_part(set_speece(str5));
// int x =0;
// // while (str[x])
// // {
// //     printf("%s\n",str[x]);
// //     x++;
// // }
// // // printf("x==%d\n",x);
// // // printf("--------------------\n");
// // // printf("cmd=%s\n",get_cmd2(str) ? get_cmd2(str):"(null)");
// // // char **flags=get_flags2(str);
// // // x =0;
// // // while (flags && flags[x])
// // // {
// // //     printf("flag%d =%s\n",x,flags[x]);
// // //     x++;
// // // }
// // x =0;

// // char **args =get_args(str); 
// // while (args[x])
// // {
// //     printf("arg[%d]=%s\n",x,args[x]);
// //    x++;
// // }



// // // get_args(str);
// // // printf("%s\n" , whithout_q("    cat ffr"));
// // x =0;
// t_out *out =get_out(str);
// while (out[x].out)
// {
//     printf("out file [%d]:%s\n",x,out[x].out);
//     printf("is append [%d]:%d\n",x,out[x].is_a);
//     x++;
// }
// x =0;
// t_inp *inp =get_inp(str);
// while (inp[x].inp)
// {
//     printf("inp file [%d]:%s\n",x,inp[x].inp);
//     printf("is Heredoc [%d]:%d\n",x,inp[x].is_h);
//     x++;
// }




// }
