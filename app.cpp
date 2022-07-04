



using namespace std;


#include <iostream>
#include <fstream>
#include <bit>
#include<vector>
#include<algorithm>
#include<numeric>
uint32_t swap_endian(uint32_t val) {
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

int main(int argc, char** argv)
{
	std::ifstream file(argv[1], std::ios::in | std::ios::binary);
	int32_t M,Nitemsi,Nrowsi,Ncolumnsi;
	file.read(reinterpret_cast<char *>(&M), sizeof(M));
	file.read(reinterpret_cast<char *>(&Nitemsi), sizeof(Nitemsi));
	file.read(reinterpret_cast<char *>(&Nrowsi), sizeof(Nrowsi));
	file.read(reinterpret_cast<char *>(&Ncolumnsi), sizeof(Ncolumnsi));

	int32_t Nitems = swap_endian(Nitemsi);
	int32_t Ncolumns = swap_endian(Ncolumnsi);
	int32_t Nrows= swap_endian(Nrowsi);
	std::cout<<M<<" "<<Nitems<<" "<<Nrows<<" "<<Ncolumns<<std::endl;
	int32_t Nrows2,Ncolumns2;

	Nrows2=Nrows/2;
	Ncolumns2=Ncolumns/2;
	std::ofstream fileo((argv[1]+std::to_string(Nrows2)+std::to_string(Ncolumns2)).c_str(), std::ios::out | std::ios::binary);
	fileo.write(reinterpret_cast<char *>(&M), sizeof(M));
	int32_t Nrowsse=swap_endian(Nrows2);
	int32_t Ncolumnsse=swap_endian(Ncolumns2);
	fileo.write(reinterpret_cast<char *>(&Nitemsi), sizeof(Nitemsi));
	fileo.write(reinterpret_cast<char *>(&Nrowsse), sizeof(Nrowsse));
	fileo.write(reinterpret_cast<char *>(&Ncolumnsse), sizeof(Ncolumnsse));

	for(auto i=0;i<Nitems;i++)
	{

		std::vector<uint8_t> in(Nrows*Ncolumns);
		int var2=0;
		std::for_each(in.begin(),in.end(),[&file,&var2,&Nrows](auto & item){
				file.read(reinterpret_cast<char *>(&item), sizeof(item));
				/*std::cout<<(int(item))<<" ";
				  if(++var2%Nrows==0)std::cout<<std::endl;
				  */
				});

		std::vector<uint8_t> out(Nrows2*Ncolumns2);
		//	std::cout<<"**********************************"<<std::endl;
		int co=0;
		for(auto c=0;c<Ncolumns;c++)
		{
			for(auto r=0;r<Nrows;r++)
			{
				if(r%2==0&&c%2==0)
				{
					int ind=r+c*Nrows;
					out[co]=(in[ind]+in[ind+1]+in[ind+Ncolumns]+in[ind+Ncolumns+1])/4;
					co++;
				}

			}
		}
		int var=0;
		std::for_each(out.begin(),out.end(),[&fileo,&var,&Nrows2](auto & item){
				fileo.write(reinterpret_cast<char *>(&item), sizeof(item));
				/*			std::cout<<(int(item))<<" ";
							if(++var%Nrows2==0)std::cout<<std::endl;*/
				});
		//std::cout<<std::endl;
	}
	return 0;
}
