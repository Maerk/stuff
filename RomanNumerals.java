package it.unimi.di.sweng.lab01;

public class RomanNumerals {
	private int key[] = {1000,500,100,50,10,5,1};
	private char val[] = {'M','D','C','L','X','V','I'};
	public String arabicToRoman(int num)
	{
		if(num<=0)
			throw new IllegalArgumentException();
		String ret = "";

		int ind = 0;
		while(num>0 && ind<key.length)
		{
			int i,t,c;
			if(ind>=0 && ind <=2) {c=100; t=2;}
			else if(ind>2 && ind<=4) {c=10; t=4;}
			else {c=1; t=6;}
			switch(i=(num/c))
			{
				case 4:
					ret += val[t];
					ret += val[t-1];
					num -= i*c;
					break;
				case 9:
					ret += val[t];
					ret += val[t-2];
					num -= i*c;
					break;
			}
			while(num>=key[ind])
			{
				ret += val[ind];
				num -= key[ind];
			}
			ind++;
		}
		return ret;
	}
	public int romanToArabic(String str)
	{
		int num = 0;
		int ind = val.length-1;
		int i = str.length()-1;
		int count = 0;
		while(i>=0)
		{
			if(str.charAt(i) == val[ind])
			{
				num += key[ind];
				i--;
				count++;
			}
			else
			{
				//controllo sottrazione
				boolean found = false;
				for(int j=ind; j<val.length; j++)
				{
					if(str.charAt(i) == val[j])
					{
						if((ind<2 && j!=2) || (ind>2 && ind<4 && j!=4) || (ind>4 && j!=6))
							ind=-1;
						else
						{
							num -= key[j];
							i--;
							count++;
							found = true;
						}
						break;
					}
				}
				if(!found)
				{
					ind--;
					count = 0;
				}
			}
			if(count>3 || ind<0)
				throw new IllegalArgumentException("Invalid Roman numeral");
		}
		return num;
	}
}
