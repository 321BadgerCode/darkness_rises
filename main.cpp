//badger
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "./h/const.h"
#include "./h/image.h"
#include "./h/obj.h"
#include "./h/player.h"

using namespace std;

int main(){
	//setup window.
	sf::RenderWindow window(sf::VideoMode(800,600),"DARKNESS RISES!");

	//std..
	image sq=*new image("./assets/sq.png",sf::Vector2f(0,0),sf::Vector2f(.1,.1));

	//player.
	player pl1(1000,*new obj(100,10,100,10,sq));

	//platforms.
	image p1("./assets/sq.png",sf::Vector2f(200,500),sf::Vector2f(.5,.1));
	image p2("./assets/sq.png",sf::Vector2f(400,400),sf::Vector2f(.1,.01));
	image platforms[]={p1,p2};

	//enemies.
	obj e1(100,10,200,10,*new image("./assets/enemy.jpg",sf::Vector2f(300,350),sf::Vector2f(.1,.1)));
	obj enemies[]={e1};

	//clock.
	sf::Clock clock;

	//run the program as long as the window is open.
	while(window.isOpen()){
		//event handler.
		sf::Event event;

		while(window.pollEvent(event)){
			//close window.
			if(event.type==sf::Event::Closed){
				window.close();
			}
		}

		//delta time to account for frame rate(same speed despite CPU,etc.).
		float delta_time=clock.restart().asSeconds();

		//keyboard movement.
		sf::Vector2f mov(0,0);
		sf::Vector2f d_mov(0,0);
		sf::Vector2f vel(0,0);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(!(pl1.hit>>1)){mov.x-=pl1.speed*delta_time;}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(!(pl1.hit>>2)){mov.x+=pl1.speed*delta_time;}
		}
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))&&pl1.hit>>3){
			vel.y=-pl1.jump_force*delta_time;
			mov+=vel;
		}

		d_mov+=mov;

		float speed=sqrt((d_mov.x*d_mov.x)+(d_mov.y*d_mov.y));
		float max_speed=100;
		if (speed>max_speed){
			d_mov.x*=max_speed/speed;
			d_mov.y*=max_speed/speed;
		}

		mov+=d_mov;

		d_mov.x*=0.9;
		d_mov.y*=0.9;

		//collision w/ player.
		cout<<(int)pl1.hit<<endl;
		for(image platform:platforms){
			if(!(pl1.hit>>3)){pl1.hit=pl1.get_collide(platform);}
			vel.y=pl1.hit>>3?0:pl1.weight*delta_time;
		}
		for(obj enemy:enemies){
			if(pl1.is_collide(enemy)){
				pl1.health-=enemy.damage;
			}
		}

		//player death.
		if(pl1.health<=0){
			window.close();
		}

		//move player every frame.
		mov+=vel;
		pl1.move(mov);

		//update window every frame & show all object on screen.
		window.clear();
		window.draw(pl1);
		for(image platform:platforms){
			window.draw(platform);
		}
		for(obj enemy:enemies){
			window.draw(enemy);
		}
		window.display();
	}

	return 0;
}