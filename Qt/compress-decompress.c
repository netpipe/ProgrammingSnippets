#include <QFile>
#include <QBytearray>
//https://www.antonioborondo.com/zipping-and-unzipping-files-with-qt/

void zip(QString filename , QString zip_filename);

void unZip(QString zip_filename , QString filename);

int main(int argc, char * argv[])
{
   zip("C:/test.txt", "C:/test.zip");
   unZip("C:/test.zip", "C:/test2.txt");

   return 0;
}

void zip(QString filename , QString zip_filename)
{
   QFile infile(filename);
   QFile outfile(zip_filename);
   infile.open(QIODevice::ReadOnly);
   outfile.open(QIODevice::WriteOnly);
   QByteArray uncompressed_data = infile.readAll();
   QByteArray compressed_data = qCompress(uncompressed_data, 9);
   outfile.write(compressed_data);
   infile.close();
   outfile.close();
}

void unZip(QString zip_filename , QString filename)
{
   QFile infile(zip_filename);
   QFile outfile(filename);
   infile.open(QIODevice::ReadOnly);
   outfile.open(QIODevice::WriteOnly);
   QByteArray uncompressed_data = infile.readAll();
   QByteArray compressed_data = qUncompress(uncompressed_data);
   outfile.write(compressed_data);
   infile.close();
   outfile.close();
}
