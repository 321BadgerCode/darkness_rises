//badger
#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

struct image:public sf::Sprite{
private:
	sf::Texture texture;
public:
	enum side{left=0b0001,right=0b0010,up=0b0100,down=0b1000};
	string filename;
	sf::Vector2f pos=sf::Vector2f(0,0);
	sf::Vector2f size=sf::Vector2f(1,1);

	image(const string& filename,const sf::Vector2f pos=sf::Vector2f(0,0),const sf::Vector2f size=sf::Vector2f(1,1)):filename(filename),pos(pos),size(size){
		this->set_load();
	}
	image(image& img){
		this->texture=img.texture;
		this->filename=img.filename;
		this->pos=img.pos;
		this->size=img.size;
		this->set_load();
	}
	void set_load(){
		this->texture.loadFromFile(this->filename);
		this->setTexture(this->texture);
		this->setPosition(this->pos);
		this->setScale(this->size);
	}
	virtual sf::Sprite get() const {return sf::Sprite(*this);}
	bool is_collide(image image2){
		return (*this).getGlobalBounds().intersects(image2.getGlobalBounds());
	}
	uint8_t get_collide(image image2){
		uint8_t collide=0;
		if((*this).is_collide(image2)){
			sf::Vector2f difference=image2.getPosition()-(*this).getPosition();

			if(difference.x<0){
				collide|=side::left;
			}
			else if(difference.x>0){
				collide|=side::right;
			}

			if(difference.y<0){
				collide|=side::up;
			}
			else if(difference.y>0){
				collide|=side::down;
			}
		}
		return collide;
	}
	side get_side(image image2){
		return *new side(get_side(image2));
	}
	/*image(const sf::Color& color,const sf::Vector2f& size){
		sf::RectangleShape rect(size);
		rect.setFillColor(color);
		texture.create(rect.getSize().x,rect.getSize().y);
		sprite.setTexture(texture);
		sprite.setPosition(pos);
	}*/
	//sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(sprite.getTexture().getSize())));
};
//FIXME: `image.h` default to sq. when img. not def..