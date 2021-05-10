#pragma once
#include <exception>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>


using std::vector;
using std::map;
using std::string;
using std::exception;

class ImageLoader {

    map<string, sf::Image> images;
    ImageLoader(){}
    ImageLoader(const ImageLoader&)  = delete;
    ImageLoader(const ImageLoader&&) = delete;
    ImageLoader& operator=(const ImageLoader&)  = delete;
    ImageLoader& operator=(const ImageLoader&&) = delete;
    
    void load_file(string name) {

        sf::Image i;
        if (!i.loadFromFile(name)) {

            throw std::exception("Don't find image file");

        }
        images[name] = i;

    }

public:

    static ImageLoader& get_instance() {

        static ImageLoader theSingleInstance;
        return theSingleInstance;

    }

    sf::Image get_image(string name) {

        if (images.find(name) == images.end()) {

            load_file(name);

        }
        return images[name];

    }

};