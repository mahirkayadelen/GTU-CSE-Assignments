#ifndef MYCODE_H
#define MYCODE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Media {
public:
    void set_entities(vector<string> v)
    {
        int i;
        vector<string>::iterator itr = v.begin();

        for (i = 0; itr != v.end(); itr++, i++)
            entities[i] = *itr;

        field_number = i;
    }

    string get_data() const
    {
        stringstream ss;
        for (int i = 0; i < field_number; i++)
        {
            ss << "\"" << entities[i] << "\"";
            if (i + 1 != field_number)
                ss << " ";
        }
        ss << endl;
        string s = ss.str();
        return s;
    }

    string get_title() const { return entities[0]; }
    int get_field_number() { return field_number; }
    string get_one_entity(int index) const { return entities[index]; }
    vector<string> get_fields() { return vect; }


protected: // for access vector in inherited class
    string entities[5];
    int field_number;
    vector<string> vect;
};

class Book : public Media {
public:
    Book() {
        vect = {"\"title\"", "\"authors\"", "\"year\"", "\"tags\""};
    }

    void sort_each(vector<Book> objects, int i, ofstream &f)
  {
    if (i == 0)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[0] < rhs.entities[0]; });
    if (i == 1)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[1] < rhs.entities[1]; });
    if (i == 2)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[2] < rhs.entities[2]; });
    if (i == 3)
      sort(objects.begin(), objects.end(), [](const Book &lhs, const Book &rhs)
           { return lhs.entities[3] < rhs.entities[3]; });
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
      f << it->get_data();
    }
  }

};

class Music : public Media {
public:
    Music() {
        vect = {"\"title\"", "\"artists\"", "\"year\"", "\"genre\""};
    }
  /* sorts according the selected area  */
  void sort_each(vector<Music> objects, int i, ofstream &f)
  {
    if (i == 0)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[0] < rhs.entities[0]; });
    if (i == 1)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[1] < rhs.entities[1]; });
    if (i == 2)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[2] < rhs.entities[2]; });
    if (i == 3)
      sort(objects.begin(), objects.end(), [](const Music &lhs, const Music &rhs)
           { return lhs.entities[3] < rhs.entities[3]; });
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
      f << it->get_data();
    }
  }
};

class Movie : public Media {
public:
    Movie() {
        vect = {"\"title\"", "\"director\"", "\"year\"", "\"genre\"", "\"starring\""};
    }
  /* sorts according the selected area  */
  void sort_each(vector<Movie> objects, int i, ofstream &f)
  {
    if (i == 0)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[0] < rhs.entities[0]; });
    if (i == 1)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[1] < rhs.entities[1]; });
    if (i == 2)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[2] < rhs.entities[2]; });
    if (i == 3)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[3] < rhs.entities[3]; });
    if (i == 4)
      sort(objects.begin(), objects.end(), [](const Movie &lhs, const Movie &rhs)
           { return lhs.entities[4] < rhs.entities[4]; });
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
      f << it->get_data();
    }
  }
};




//MEDIA CATALOG TEMPLATE
template <class MediaType>
class MediaCatalog
{
public:
  void add_entry(MediaType mediaItem) { catalogEntries.push_back(mediaItem); }

  string get_catalog_info()
  {
    stringstream ss;
    ss << catalogEntries.size() << " unique entries" << endl;
    return ss.str();
  }

  string get_title(int index) { return catalogEntries[index].get_title(); }

  vector<string> get_fields() { return catalogEntries[0].get_fields(); }

  bool check_duplicate(string title)
  {
    for (const auto& item : catalogEntries)
    {
      if (item.get_title() == title)
        return false;
    }
    return true;
  }

  void search_in_catalog(string str, int index, ofstream &outputFile)
  {
    string delimiter = "\"", processed_string;
    size_t pos = 0;
    string token;
    int count = 0;
    while ((pos = str.find(delimiter)) != string::npos)
    {
      token = str.substr(0, pos);
      if (count == 1)
        processed_string = token;
      str.erase(0, pos + delimiter.length());
      count++;
    }

    for (const auto& item : catalogEntries)
    {
      if (item.get_one_entity(index).find(processed_string) != string::npos)
        outputFile << item.get_data();
    }
  }

  void sort_entries(int type, ofstream &outputFile)
  {
    MediaType mediaItem;
    mediaItem.sort_each(catalogEntries, type, outputFile);
  }

private:
  vector<MediaType> catalogEntries;
};

//PARSE LINES TEMPLATE FUNCTION
template <class MediaType>
string parse_and_assign_fields(MediaType& mediaItem, string line)
{
    int count = 0;
  string delimiter = "\""; 
  size_t pos = 0;
  string token;
  vector<string> fields;

  while ((pos = line.find(delimiter)) != string::npos)
  {
    token = line.substr(0, pos);
    if (count % 2 != 0)
      fields.push_back(token);
    line.erase(0, pos + delimiter.length());
    count++;
  }

  mediaItem.set_entities(fields);
  return fields[0];
}

/*Search and sort */
template <class MediaType>
void search_and_sort(MediaCatalog<MediaType>& catalog, ofstream &outputFile)
{
  ifstream command_file("commands.txt");
  string line;

  while (getline(command_file, line))
  {
    stringstream lineStream(line); 
    string command;
    lineStream >> command;
    bool validCommand = true;
    vector<string> fields = catalog.get_fields();

    if (command == "search")
    {
      string searchString;
      lineStream >> searchString;
      lineStream >> command;
      if (command == "in")
      {
        lineStream >> command;
        for (int i = 0; i < fields.size(); i++)
        {
          if (command == fields[i])
          {
            outputFile << line << endl;
            catalog.search_in_catalog(searchString, i, outputFile);
            validCommand = false;
          }
        }
        if (validCommand)
        {
          outputFile << "Exception: command is wrong" << endl;
          outputFile << line << endl;
        }
      }
    }
    else if (command == "sort")
    {
      lineStream >> command;
      for (int i = 0; i < fields.size(); i++)
      {
        if (command == fields[i])
        {
          outputFile << line << endl;
          catalog.sort_entries(i, outputFile);
          validCommand = false;
        }
      }
      if (validCommand)
      {
        outputFile << "Exception: command is wrong" << endl;
        outputFile << line << endl;
      }
    }
  }
}

#endif