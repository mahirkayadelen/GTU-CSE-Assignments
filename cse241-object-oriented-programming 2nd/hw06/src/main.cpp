#include "utils.h"

int main()
{
  ifstream data_file("data.txt");
  ofstream output_file("output.txt");
  string str;

  data_file >> str;

  if (str == "book")
  {
    output_file << "Catalog Read: book" << endl;
    MediaCatalog<Book> catalog;
    Book *book = new Book;

    getline(data_file, str);
    while (getline(data_file, str))
    {
      if (catalog.check_duplicate(parse_and_assign_fields(*book, str)))
      {
        if (4 != book->get_field_number())
          output_file << "Exception: missing field" << endl << book->get_data();
        else
          catalog.add_entry(*book);
      }
      else
      {
        output_file << "Exception: " << (4 != book->get_field_number() ? "missing field" : "duplicate entry") << endl;
        output_file << book->get_data();
      }
    }
    output_file << catalog.get_catalog_info();
    search_and_sort(catalog, output_file);
  }
  else if (str == "music")
  {
    output_file << "Catalog Read: music" << endl;
    MediaCatalog<Music> catalog;
    Music *music = new Music;

    getline(data_file, str);
    while (getline(data_file, str))
    {
      if (catalog.check_duplicate(parse_and_assign_fields(*music, str)))
      {
        if (4 != music->get_field_number())
          output_file << "Exception: missing field" << endl << music->get_data();
        else
          catalog.add_entry(*music);
      }
      else
      {
        output_file << "Exception: " << (4 != music->get_field_number() ? "missing field" : "duplicate entry") << endl;
        output_file << music->get_data();
      }
    }
    output_file << catalog.get_catalog_info();
    search_and_sort(catalog, output_file);
  }
  else if (str == "movie")
  {
    output_file << "Catalog Read: movie" << endl;
    MediaCatalog<Movie> catalog;
    Movie *movie = new Movie;

    getline(data_file, str);
    while (getline(data_file, str))
    {
      if (catalog.check_duplicate(parse_and_assign_fields(*movie, str)))
      {
        if (5 != movie->get_field_number())
          output_file << "Exception: missing field" << endl << movie->get_data();
        else
          catalog.add_entry(*movie);
      }
      else
      {
        output_file << "Exception: " << (5 != movie->get_field_number() ? "missing field" : "duplicate entry") << endl;
        output_file << movie->get_data();
      }
    }
    output_file << catalog.get_catalog_info();
    search_and_sort(catalog, output_file);
    output_file.close();
  }

  return 0;
}