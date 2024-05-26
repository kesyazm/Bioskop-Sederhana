#include<iostream>
#include<map>
#include<fstream>


using namespace std;
void logo_perusahaan(){
    cout << "============================================" << endl;
    cout << " ____   _              _                    " << endl;             
    cout << "|  _ \\ (_)            | |                   " << endl;
    cout << "| |_) | _   ___    ___| | __ ___  _ __     " << endl;
    cout << "|  _ < | | / _ \\ / __|| |/ // _ \\| '_ \\    " << endl;
    cout << "| |_) || || (_) |\\__ \\|   <| (_) |||_)|   " << endl;
    cout << "|____/ |_| \\___/ |___/|_|\\_/\\___/| .__/    " << endl;
    cout << "                                 | |       " << endl; 
    cout << "                                 |_|       " << endl;
    cout << "============================================" << endl;
    cout << endl;
}

void menu_user(){
    cout << "============================================" << endl;
    cout << "| 1. User                                  |" << endl;
    cout << "| 2. Admin                                 |" << endl;
    cout << "| 3. Exit                                  |" << endl;
    cout << "| Input Type : ";
}
int list_movie(){
    map <int,string> judul_movie;

    judul_movie[1] = "Haikyu!! The Dumpster Battle";
    judul_movie[2] = "Kung Fu Panda 4";
    judul_movie[3] = "How to Make Millions Before Grandma Dies";
    judul_movie[4] = "The Architecture of Love";
    judul_movie[5] = "Vina: Sebelum 7 Hari";

    cout << "============================================" << endl;
    cout << "| Judul Movie :" << endl;
    for(const auto& var : judul_movie){
        cout << "| " << var.first << ". " << var.second << endl;
    }
    cout << "| 0.Kembali" << endl;
    cout << endl;
    return judul_movie.size();

}

void SelamatTinggal(){
    cout << "Selamat Tinggal !" << endl;
}

void clearScreen(){
    cout << "\033[2J\033[H";
}

void error_message(string pesan_error){
    string dummy;
    cout << pesan_error << endl;
    cout << "Enter to continue..." << endl;
    getline(cin,dummy);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void catatan_pembelian(int id, string nama_pengguna){
        string nama_file = "Log_pembelian";
        string final_nama_file = nama_file +to_string(id)+".txt";

        ofstream outputFile(final_nama_file,ios::app);
        if(outputFile.is_open()){
            outputFile << nama_pengguna << "\n";
            outputFile.close();
        }
        return;
}

bool list_pemeblian_berdasarkan_id_file(int id){
    int select;
    string nama_file = "Log_pembelian";
    string final_nama_file = nama_file +to_string(id)+".txt";
    ifstream openfile(final_nama_file,ifstream::in);
    if(openfile.is_open()){
        cout << "| List nama pembeli berdasarkan id file " << id << " : " << endl;
        string name;
        while(getline(openfile,name)){
            cout << "| " << name << endl;
        } 
        openfile.close();
        return true;
    }else{
        return false;
    }

}

void main_User(){
    int main_select , jumlah_filem , jumlah_pembelian, pembayaran , total_harga,kembalian;
    int semua_harga_tike = 20000;
    string nama_pengguna;
    bool status = true;
    while(status){
        try{
            jumlah_filem = list_movie();
            cout << "============================================" << endl;
            cout << "| User Select : " ;
            if(!(cin >> main_select)){
                throw runtime_error("Inputan kurang tepat");
            }
            if(main_select == 0){
                return;
            }
            if( main_select > jumlah_filem){
                throw runtime_error("Inputan tidak ditemukan");
            }
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            clearScreen();

            // pembatasan pembelian tiket
            cout << "============================================" << endl;
            cout << "| Untuk berapa user : ";
            if(!(cin >> jumlah_pembelian)){
                throw runtime_error("Inputan kurang tepat");
            }
            if( jumlah_pembelian > 2){
                throw runtime_error("Tidak boleh melebihi 2 orang");
            }
            clearScreen();
            total_harga = semua_harga_tike * jumlah_pembelian;
            cout << "============================================" << endl;
            cout << "| Total harga yang harus dibayarkan sebesar : " << total_harga << endl;
            cout << "| Masukkan nominal uang yang diberikan user : " ;
            if(!(cin >> pembayaran)){
               
                throw runtime_error("Inputan tidak sesuai");
            }
            if(pembayaran < total_harga){
               
                throw runtime_error("Uang anda kurang !");
            }
            kembalian = pembayaran - total_harga;
            cout << "| Total Kembalian anda sebesar : " << kembalian << endl;
            cin.ignore();
            
            for(int i = 0 ; i < jumlah_pembelian ; i++){
                cout << "Masukan nama pembeli ke " << i + 1 << " : " ;
                if(!(getline(cin, nama_pengguna))){
                    throw runtime_error("input tidak sesuai");
                } 
                catatan_pembelian(main_select,nama_pengguna);
            }
            clearScreen();
            cout << "Terima kasih telah melakukan pembelian di Bioskop ini !" << endl;
            cin.get();
            status = false;

        }catch(const exception& e){
            error_message(e.what());
        }
        clearScreen();
    }
}

void main_Admin(){
    int menu_select , jumlah_filem;
    bool value_exit;
    string username = "admin";
    string password = "123456";
    string input_user, input_password;
    bool status = true;
    while(status){
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        try{
            cout << "Username : " ;
            if(!(getline(cin,input_user))){
                throw runtime_error("inputan tidak sesuai");
            }
            cout << "Password : " ;
            if(!(getline(cin,input_password))){
                throw runtime_error("inputan tidak sesuai");
            }

            if(username == input_user && password == input_password){
                clearScreen();
                jumlah_filem = list_movie();
                if(!(cin >> menu_select)){
                    throw runtime_error("Inputan kurang tepat");
                }
                if(menu_select == 0){
                    return;
                }
                if(menu_select > jumlah_filem){
                    throw runtime_error("inputan tidak ditemukan");
                }
               cin.ignore(numeric_limits<streamsize>::max(),'\n');
               value_exit = list_pemeblian_berdasarkan_id_file(menu_select);
                if(value_exit == false){
                    cout << "Tidak ada pembeli yang masuk !" << endl;
                }
                cout << "Tekan enter untuk kembali ke menu awal " << endl;
                cin.get();
                status = false;
            }else{
                cout << "User dan password anda salah !" << endl;
                status = true;
            }
            
        }catch(const exception& e){
            error_message(e.what());
            status = true;
        }
    }
}

int main(){
    int menu_select = 3;
    bool aplikasi_status = true;
    while(aplikasi_status){
        try{
            clearScreen();
            aplikasi_status = false;
            logo_perusahaan();
            menu_user();
            if(!(cin >> menu_select)){
                throw runtime_error("input tidak valid , Harap masukan bilangan bulat");
            }
            
            switch(menu_select){
                case 1:
                    clearScreen();
                    main_User();
                    // jika user pelanggan
                break;
                case 2:
                    clearScreen();
                    main_Admin();
                    // jika user admin
                break;
                case 3:
                    clearScreen();
                    SelamatTinggal();
                    return 0;
                    // exit
                break;
                default : 
                    error_message("inputan tidak di temukan");
                break;
            }

        }catch(const exception& e){
            error_message(e.what());
        }
        aplikasi_status = true;
    }
    return 0;
}