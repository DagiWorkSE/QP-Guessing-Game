#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int gue[4],ran[4];
bool nc[10]={false};
int f[4]={0},n[6]={0};
int guess[10]={0,1,2,3,4,5,6,7,8,9};
int hqu[15],hpo[15],cqu[15],cpo[15],comp[15]={0},human[15]={0};
int possible_answers[25][4]={0000};
int checked[4],ch=0,tempo;
bool pcbool[15]={true},draw=false;
int seed=0;
void reset_game()
{
    draw=false;
    tempo=0;
    ch=0;
    guess[0]=0;
    seed=0;
    for(int i=0;i<25;i++)
    {
        for(int j=0;j<4;j++)
        {
            possible_answers[i][j]=0;
            gue[j]=0;
            ran[j]=0;
            f[j]=0;
            checked[j]=0;
        }
        if(i<10)
            nc[i]=false;
        if(i<6)
            n[i]=0;
        if(i<15)
        {
            hqu[i]=0;
            hpo[i]=0;
            cqu[i]=0;
            cpo[i]=0;
            comp[i]=0;
            human[i]=0;
            pcbool[i]=false;

        }
    }
    pcbool[0]=true;
}
bool winning_sinario()
{
    int temp=0,temp2=0;
    for(int i=0;i<24;i++)
    {
        if(possible_answers[i][0]!=0)
        {
            temp++;
            temp2=i;
        }
    }
    if(temp==1)
    {
        for(int i=0;i<4;i++)
        {
            possible_answers[24][i]=possible_answers[temp2][i];
        }
        return true;
    }
    else
    {
        tempo=temp2;
        return false;
    }
}

int random()
{
    int r=0,temp[4]={0};
    srand(time(NULL));
    for(int i=0;i<4;i++)
    {
        seed=seed + 2*rand();
        srand(seed);
        temp[i]=(rand()%9)+1;
        r=r*10+temp[i];
        int o=temp[i];
        for(int k=i;k>=0;k--)
        {
            if(o==temp[k] && k!=i)
            {
                i=-1;
                r=0;
                break;
            }
        }
        if(i==3)
        {
            int te[2]={0};
            for(int j=0;j<4;j++)
            {
                if(temp[j]<5)
                    te[0]++;
                else if(temp[j]>5)
                    te[1]++;
            }
                if(te[0]>2 || te[1]>2)
                {
                    seed/=3;
                    r=random();
                }
        }
    }
    return r;
}

void breaker(int x,int r)
{
  for(int i=3;i>=0;i--)
  {
   gue[i]=x%10;
   x=x/10;
   ran[i]=r%10;
   r=r/10;
  }
}

int checkq(int x,int r)
{
breaker(x,r);
int q=0;
for(int i=0;i<4;i++)
{
  for(int j=0;j<4;j++)
  {
    if(gue[i]==ran[j])
    q++;
  }
}
return q;
}

int checkp(int x, int r)
{
  breaker(x,r);
  int p=0;
  for(int i=0;i<4;i++)
  {
    if(gue[i]==ran[i])
    p++;
  }
return p;
}

void short_listing(int p,bool on_p=true)
{
    int d=0;
    for(int i=0;i<24;i++)
    {
        if(!on_p)
        {
            if(possible_answers[i][p]==gue[p])
            {
                for(int j=0;j<4;j++)
                    possible_answers[i][j]=0;
            }
        }
        else
        {
            if(possible_answers[i][p]!=gue[p])
            {
                for(int j=0;j<4;j++)
                    possible_answers[i][j]=0;
            }
        }
    }
}

int return_possition(int r,int z)
{
    breaker(comp[z],r);
    for(int i=0;i<4;i++)
    {
        bool temp_unchecked=true;
        for(int j=0;j<4;j++)
            {
                if(gue[i]==checked[j])
                    temp_unchecked=false;
            }
        if(nc[gue[i]] && temp_unchecked)
        {
            checked[ch]=gue[i];
            ch++;
            return i+1;
        }
    }
    return 0;
}
void reset_checked()
{
    for(int i=0;i<4;i++)
        checked[i]=0;
    ch=0;
}

void set_answers()
{
    int counter=0,t=0;
    for(int i=0;i<4;i++)
    {
        for(int q=counter;q<counter+6;q++)
                possible_answers[q][t]=f[i];;
        t++;
        for(int j=0;j<4;j++)
        {
            if(i==j)
                continue;
            else
            {
                for(int q=counter;q<counter+2;q++)
                    possible_answers[q][t]=f[j];
                t++;
                for(int k=0;k<4;k++)
                {
                    if(k==j || k==i)
                        {
                            if(k==3)
                                t--;
                            continue;
                        }
                    else
                    {
                        possible_answers[counter][t]=f[k];
                        t++;
                        for(int l=0;l<4;l++)
                        {
                            if(l==i || l==j || l==k)
                                continue;
                            else
                            {
                                possible_answers[counter][t]=f[l];
                                t--;
                                counter++;
                            }
                        }
                    }
                    if(k==3)
                        t--;
                }
            }
            if(j==3)
                t=0;
        }
    }
}

int guess_digit(int g)
{
    int counter=0;
    while (g!=0)
    {
        counter++;
        g/=10;
    }
    return counter;
}

bool inline win(int q,int p)
{
  if(p==4 && q==4)
  {
    return true;
  }
  else
    return false;
}

int tc(int d_limit=1,int u_limit=10)
{
  int count=0;
  for(int i=d_limit;i<u_limit;i++)
  {
    if(nc[i]==true)
      count++;
  }
  return count;
}

int pcguess(int x,int y){
    for(int i=x;i<y;i++)
    {
        guess[0]=guess[0]*10+guess[i];
    }
    int temporary=guess[0];
    guess[0]=0;
    return temporary;
}
void output(int current_guess,bool hu=true)
{
    int cx=1;
    if(hu)
    {
        system("cls");
        cout<<"\n\n\t\t\t\t'''''''''''''''''''''''''''''''''''''''''\n";
        cout<<"\t\t\t\t|  Welcome to the one and only QP game  |\n";
        cout<<"\t\t\t\t| Your going against a tough contender  |\n";
        cout<<"\t\t\t\t|\t    SO GOOD LUCK\t\t|\n";
        cout<<"\t\t\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n";
    }
    string xin=(hu)?"USER":"Computer";
    cout<<"\n\t\t\t\t"<<xin<<"\n\n";
    cout<<"|\tTry\t|\tGuess\t|\tQuality\t|\tPosition\t|\n\n";
    for(int i=0;i<=current_guess;i++)
    {
        if(hu)
        {
            if(human[i]==0)
                break;
            else
                cout<<"|\t"<<i+1<<"\t|\t"<<human[i]<<"\t|\t"<<hqu[i]<<"\t|\t"<<hpo[i]<<"\t\t|\n";
        }
        else
        {
            if(comp[i]==0)
                cx--;
            else
                cout<<"|\t"<<i+cx<<"\t|\t"<<comp[i]<<"\t|\t"<<cqu[i]<<"\t|\t"<<cpo[i]<<"\t\t|\n";
        }
    }
}
void inline checkpc(int r,int z){
    /*cqu[z]=checkq(comp[z],r);
    cpo[z]=checkp(comp[z],r);*/
    breaker(comp[z],r);
    cout<<"\n\n\t\t\tPC guess : "<<comp[z];
    cout<<"\n\nEnter Quality : ";
    cin>>cqu[z];
    cout<<"\n\nEnter Position : ";
    cin>>cpo[z];
    output(z);
    output(z,false);
}
int main()
{
char again;
do
{
    bool found[2]={false,false};
    int x,r=random(),offset=1,pc_number=0,checker=0;
    output(-1);
    output(-1,false);
    for(int z=0;z<15;z++)
    {
        cout<<"\n\nGuess : ";
        cin>>x;
        human[z]=x;
        hqu[z]=checkq(x,r);
        hpo[z]=checkp(x,r);
        output(z);
        bool temp=false;
        int temp2;
        for(int h=4;h<8;h++)
            {
                if(pcbool[h]==true)
                {
                    temp=true;
                    temp2=h;
                }
            }
        if(pcbool[0])
        {
            comp[pc_number]=pcguess(1,5);
            checkpc(r,pc_number);
            pcbool[0]=false;
            pcbool[1]=true;
        }
        else if(pcbool[1])
        {
            comp[pc_number]=pcguess(6,10);
            checkpc(r,pc_number);
            if(cqu[pc_number]+cqu[pc_number-1]==4)
            {
                n[0]=5;
                nc[5]=false;
            }
            else
            {
                f[0]=5;
                nc[5]=true;
            }
            pcbool[1]=false;
            if(cqu[0]==0)
            {
                for(int i=1;i<5;i++)
                    {
                        if(nc[5])
                            n[i-1]=i;
                        else
                        {
                            n[i]=i;
                            f[i-1]=i;
                            nc[i]=true;
                        }
                    }
                found[0]=true;
                pcbool[3]=true;
                pc_number++;
            }
            else if(cqu[1]==0)
            {
                for(int i=6;i<10;i++)
                    {
                        if(nc[5])
                            n[i-6]=i;
                        else
                        {
                            n[i-5]=i;
                            f[i-6]=i-5;
                            nc[i-5]=true;
                        }
                    }
                found[1]=true;
                pcbool[2]=true;
            }
            else
            {
                pcbool[2]=true;
            }
        }
        else if(pcbool[2])
        {
            comp[pc_number]=pcguess(2,6);
            checkpc(r,pc_number);
            if(cqu[pc_number]-int(nc[5])!=cqu[pc_number-2])
            {
                f[tc()]=1;
                nc[1]=true;
            }
            else
            {
                n[pc_number-offset-tc()]=1;
                nc[1]=false;
            }
            if(cqu[0]-nc[1]==3)
            {
                f[tc()]=2;
                nc[2]=true;
                f[tc()]=3;
                nc[3]=true;
                f[tc()]=4;
                nc[4]=true;
                found[0]=true;
            }
            pcbool[2]=false;
            if(found[1])
            {
                pc_number++;
                pcbool[4]=true;
            }
            else
            {
                pcbool[3]=true;
            }
        }
        else if(pcbool[3])
        {
            comp[pc_number]=pcguess(5,9);
            checkpc(r,pc_number);
            if(cqu[pc_number]-int(nc[5])!=cqu[pc_number-2])
            {
                f[tc()]=9;
                nc[9]=true;
            }
            else
            {
                n[pc_number-offset-tc()]=9;
                nc[9]=false;
            }
            if(cqu[1]-nc[9]==3)
            {
                f[tc()]=6;
                nc[6]=true;
                f[tc()]=7;
                nc[7]=true;
                f[tc()]=8;
                nc[8]=true;
                found[1]=true;
            }
            pcbool[3]=false;
            if(found[0])
            {
                pc_number=5;
                pcbool[6]=true;
            }
            else
            {
                pcbool[4]=true;
            }
        }
        else if(temp)
        {
            int temp_i=0,temp_j=0;
            while(guess_digit(guess[0])<3)
            {
                if(f[temp_i]!=0)
                {
                    guess[0]=guess[0]*10+f[temp_i];
                    temp_i++;
                }
                else
                {
                    guess[0]=guess[0]*10+n[temp_j];
                    temp_j++;
                }
            }
            int temp=(pc_number==4 || pc_number==5)?pc_number-2:pc_number;
            guess[0]=guess[0]*10+guess[temp];
            comp[pc_number]=guess[0];
            guess[0]=0;
            checkpc(r,pc_number);
            if(cqu[pc_number]==temp_i)
            {
                n[pc_number-offset-tc()]=temp;
                nc[temp]=false;
            }
            else
            {
                f[tc()]=temp;
                nc[temp]=true;
            }
            if(pc_number==5)
            {
                if(cqu[0]-int(nc[1])-int(nc[2])-int(nc[3])!=0)//check for 4
                    {
                        f[tc()]=4;
                        nc[4]=true;
                    }
                else
                    {
                        offset=0;
                        n[pc_number-offset-tc()]=4;
                        nc[4]=false;
                    }
            }
            if(pc_number==7)
            {
                if(cqu[1]-int(nc[6])-int(nc[7])-int(nc[9])!=0)
                {
                    f[tc()]=8;
                    nc[8]=true;
                }
                else
                {
                    n[pc_number-offset-tc()]=8;
                    nc[8]=false;
                }
            }
            if(temp2==4)
            {
                if(cqu[0]-nc[1]-nc[2]==2)
                {
                    f[tc()]=3;
                    nc[3]=true;
                    f[tc()]=4;
                    nc[4]=true;
                    found[0]=true;
                }
            }
            else if(temp2==6)
            {
                if(cqu[1]-nc[6]-nc[9]==2)
                {
                    f[tc()]=7;
                    nc[7]=true;
                    f[tc()]=8;
                    nc[8]=true;
                    found[1]=true;
                }
            }
            pcbool[temp]=false;
            if(found[0] && temp2==4)
            {
                pcbool[6]=true;
                pc_number++;
            }
            else if(found[1] && temp2==6)
            {
                pcbool[8]=true;
                pc_number++;
            }
            else
            {
                pcbool[temp2+1]=true;;
            }
        }
        else if(pcbool[8])
        {
            for(int i=checker;i<pc_number;i++)
            {
                if(comp[i]==0)
                {
                    continue;
                }
                if(cqu[i]==cpo[i])
                {
                    for(int j=0;j<cqu[i];j++)
                    {
                        int t=0;
                        t=return_possition(r,i);
                        if(t!=0)
                        {
                            short_listing(t-1);
                        }
                    }
                    reset_checked();
                }
                else if(cpo[i]==0)
                {
                    for(int j=0;j<cqu[i];j++)
                    {
                        int t=0;
                        t=return_possition(r,i);
                        if(t!=0)
                    {
                            if(possible_answers[24][0]==0)
                            {
                                short_listing(t-1,false);
                            }
                        }
                    }
                    reset_checked();
                }
                else if((cpo[i]==1 && cqu[i]!=1) || cpo[i]==2)
                {
                    int pos[4]={0},t=0;
                    int temp_short[24]={0};
                    breaker(comp[i],r);
                    for(int j=0;j<4;j++)
                        {
                            if(nc[gue[j]])
                            {
                                pos[t]=j;
                                t++;
                            }
                        }
                        t=0;
                    for(int j=0;j<24;j++)
                    {
                        //experimental
                        if(cqu[i]!=4 && cpo[i]==1)
                        {
                            bool tt[3]={(gue[pos[0]]!=possible_answers[j][pos[0]]),(gue[pos[1]]!=possible_answers[j][pos[1]]),(gue[pos[2]]!=possible_answers[j][pos[2]])};
                            if(cqu[i]==2)
                                tt[2]=true;
                            bool poss_v[4]={(!tt[0] && !tt[1]),(!tt[0] && !tt[2]),(!tt[1] && !tt[2]),(tt[0] && tt[1] && tt[2])};
                            if(poss_v[0] || poss_v[1] || poss_v[2] || poss_v[3])
                            {
                                for(int k=0;k<4;k++)
                                    possible_answers[j][k]=0;
                            }
                        }
                        else if(cpo[i]==2)
                        {
                            for(int k=0;k<3;k++)
                            {
                                for(int l=k+1;l<4;l++)
                                {
                                    if(nc[gue[k]] && nc[gue[l]])
                                    {
                                        if(gue[k]==possible_answers[j][k] && gue[l]==possible_answers[j][l])
                                        {
                                            temp_short[t]=j;
                                            t++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(cpo[i]==2)
                    {
                        for(int j=0;j<24;j++)
                        {
                            bool tt=true;
                            for(int k=0;k<t;k++)
                            {
                                if(j==temp_short[k])
                                    tt=false;
                            }
                            if(tt)
                            {
                                for(int k=0;k<4;k++)
                                {
                                    possible_answers[j][k]=0;
                                }
                            }
                        }
                    }
                }
            }
            checker=pc_number;
            if(winning_sinario())
            {
                comp[pc_number]=0;
                for(int j=0;j<4;j++)
                {
                    comp[pc_number]=comp[pc_number]*10+possible_answers[24][j];
                }
                checkpc(r,pc_number);
            }
            else
            {
                comp[pc_number]=0;
                for(int k=0;k<4;k++)
                {
                    comp[pc_number]=comp[pc_number]*10+possible_answers[tempo][k];
                    possible_answers[tempo][k]=0;
                }
                checkpc(r,pc_number);
            }
        }
        if(cqu[pc_number]==4 && pc_number<8)
        {
            for(int i=0;i<4;i++)
            {
                nc[gue[i]]=true;
            }
        }
        pc_number++;
        if(tc(0,10)==4)
        {
            for(int i=0;i<8;i++)
                pcbool[i]=false;
            pcbool[8]=true;
            set_answers();
            nc[0]=true;
            pc_number=8;
        }
        if(tc(1,5)==cqu[0] && !found[0])
        {
            found[0]=true;
        }
        else if(tc(6,10)==cqu[1] && !found[1] && z>0)
        {
            found[1]=true;
        }
    if(win(hqu[z],hpo[z]) && win(cqu[pc_number-1],cpo[pc_number-1]))
    {
        cout<<"\n\n\t\t\t\t\t'''''''''''''''''''''''''''''''''''''''''\n";
        cout<<"\t\t\t\t\t|\t\tITS A DRAW\t\t|\n";
        cout<<"\t\t\t\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n";
        break;
    }
    else if(win(cqu[pc_number-1],cpo[pc_number-1]))
                {
                cout<<"\n\n\t\t\t\t\t'''''''''''''''''''''''''''''''''''''''''\n";
                cout<<"\t\t\t\t\t|\t\tYou lost\t\t|\n";
                cout<<"\t\t\t\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n";
                break;
                }
    else if (win(hqu[z],hpo[z]))
    {
        cout<<"\n\n\t\t\t\t\t'''''''''''''''''''''''''''''''''''''''''\n";
        cout<<"\t\t\t\t\t|\t\tYou Won\t\t\t|\n";
        cout<<"\t\t\t\t\t,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n";
        break;
    }

}
cout<<"\n\nDo You Wish To Play Again ?(Y/N)\n\n : ";
cin>>again;
reset_game();
}while(again=='y' || again=='Y');
return 0;
}
