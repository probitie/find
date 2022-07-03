#include<iostream>
#include<dirent.h>
#include <filesystem>
#include <vector>
#include <queue>

namespace fs = std::filesystem;

using dir_queue_t = std::queue<fs::path>;  // очередь для директорий
using dir_queue_vector_t = std::vector<dir_queue_t >;  // вектор очередей для директорий

/// ищет файл в указаной директории(пустая строка если не найден) и добавляет все поддиректории в очередь
/// (для следующего уровня поиска в ширину)
/// УТОЧНЕНИЕ: функция не добавляет в очередь директории, которые расположены после НАЙДЕНОГО файла!!!
///             так как предполагается что далее поиск проводиться не будет
fs::path findFileInDir(const fs::path &current_dir, const std::string &filename, dir_queue_t &subdir_queue)
{

    fs::directory_iterator current_dir_it{current_dir};     // создаем итератор для указаной директории

    fs::path filepath{current_dir/filename};    // полный путь к файлу

    fs::path result{};  // если файл будет найдет то сюда запишется значение

    // проходим по всем файлам в директории
    for (const auto &element : current_dir_it)
    {

        // если это настоящий файл и его путь соответствует указаному
        if (fs::is_regular_file(element) && element.path() == filepath)
        {
            result = element;                   // ура, файл найден, останавливаем выполнение
            break;
        } else if (fs::is_directory(element))   // но если файл является директорией
        {
            subdir_queue.push(element.path());  // в таком случае добавляем в очередь для директорий
        }
    }

    return result;
}

// принимать аргументы из консоли
int main()
{

    // начинаем с корневой директории
    fs::path root{std::filesystem::current_path().root_path()};

    dir_queue_t root_level{};
    dir_queue_t level{};
    root_level.push(root);

    // обьявляем уровни - текущий ( с которого будут браться директории)
    // и следующий ( куда будут директории записываться как побочный эффект работы findFileInDir)
    dir_queue_t &current_level = root_level;  // TODO решить чет с ссылками
    dir_queue_t &next_level = level;

    // поиск в ширину
    while(true)
    {
        // каждую директорию текщуего уровня
        while()// TODO сделать вектор а не очередь - так можно будет пройтись форичем
        //     перебрать функцией на некст уровень

    }






//    DIR *directory;   // creating pointer of type dirent
//    struct dirent *x;   // pointer represent directory stream
//    directory = opendir ("C:\\SIT\\");
//    x = readdir(directory);
//    while (x != NULL)
//    {
//        std::cout << x->d_name << "\n";
//        x = readdir(directory);
//    }
//
//    std::cout << directory->dd_name;
//    closedir (directory);
}
/*
отделить ввод названия папки
выводить путь к папке

рекурс - мб -
 поиск в ширину(все элементы 1 слоя потом 2 и тд)

*/


// рекурсивный поиск но без сфайлфайн
//void Recurse(LPCTSTR pstr)
//{
//    CFileFind finder;
//
//    // build a string with wildcards
//    CString strWildcard(pstr);
//    strWildcard += _T("\\*.*");
//
//    // start working for files
//    BOOL bWorking = finder.FindFile(strWildcard);
//
//    while (bWorking)
//    {
//        bWorking = finder.FindNextFile();
//
//        // skip . and .. files; otherwise, we'd
//        // recur infinitely!
//
//        if (finder.IsDots())
//            continue;
//
//        // if it's a directory, recursively search it
//
//        if (finder.IsDirectory())
//        {
//            CString str = finder.GetFilePath();
//            cout << (LPCTSTR) str << endl;
//            Recurse(str);
//        }
//    }
//
//    finder.Close();
//}