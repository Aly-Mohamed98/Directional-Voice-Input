////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <algorithm>


double red = 0;
double blue = 200;
double Radius[25] = {20,30,20,40,30,40,30,20,30,40,40,20,20,30,20,40,40,20,30,30,20,20,40,30,40};
double x_pos[25] = {50,650,70,700,350,70,650,70,650,250,500,480,250,550,340,350,50,700,200,220,480,500,200,380,350 };
double y_pos[25] = {40,450,450,40,250,150,350,350,150,40,450,40,450,250,40,450,250,250,250,350,150,350,150,350,150 };


int rad = 0;
int count = 0;


void func()
{
    //random_shuffle(std::begin(Radius), std::end(Radius));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circles");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                rad++;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        for (int i = 0; i < 25; i++) {
            sf::CircleShape shape(Radius[i]);



            if (i == rad ) {
                red = 200;
                blue = 0;
            }

            else{
                blue = 200;
                red = 0;
            }

            shape.setFillColor(sf::Color(red, 0, blue));


            shape.setPosition(x_pos[i], y_pos[i]);
            window.draw(shape);
            // end the current frame


        }


        window.display();



    }
    // this function is started when thread.launch() is called



}
int main() {
    sf::Thread thread(&func);

    // run it

    thread.launch();

    // Check that the device can capture audio
    if (sf::SoundRecorder::isAvailable() == false) {
        std::cout << "Sorry, audio capture is not supported by your system" << std::endl;
        return EXIT_SUCCESS;
    }


    // Choose the sample rate
    unsigned int sampleRate = 44100;
    //std::cout << "Please choose the sample rate for sound capture (44100 is CD quality): ";
    //std::cin >> sampleRate;
    //std::cin.ignore(10000, '\n');

    // Wait for user input...
    std::cout << "Press enter to start recording audio";
    std::cin.ignore(10000, '\n');

    // Here we'll use an integrated custom recorder, which saves the captured data into a SoundBuffer
    sf::SoundBufferRecorder recorder;

    // Audio capture is done in a separate thread, so we can block the main thread while it is capturing
    recorder.start(sampleRate);
    std::cout << "Recording... press enter to stop";
    std::cin.ignore(10000, '\n');
    recorder.stop();

    // Get the buffer containing the captured data
    const sf::SoundBuffer &buffer = recorder.getBuffer();

    // Display captured sound informations
    std::cout << "Sound information:" << std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
    std::cout << " " << buffer.getSampleRate() << " samples / seconds" << std::endl;
    std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;

    // Choose what to do with the recorded sound data
    //char choice;
    //std::cout << "What do you want to do with captured sound (p = play, s = save) ? ";
    //std::cin >> choice;
    //std::cin.ignore(10000, '\n');


    // Choose the filename
    std::string filename;
    std::cout << "Write your number to save file : ";
    std::getline(std::cin, filename);

    // Save the buffer
    filename = filename + ".wav";

    buffer.saveToFile(filename);

    //else
    //{
    //	// Create a sound instance and play it
    //	sf::Sound sound(buffer);
    //	sound.play();

    //	// Wait until finished
    //	while (sound.getStatus() == sf::Sound::Playing)
    //	{
    //		// Display the playing position
    //		std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
    //		std::cout << std::flush;

    //		// Leave some CPU time for other threads
    //		sf::sleep(sf::milliseconds(100));
    //	}
    //}

    // Finished!
    std::cout << std::endl << "Done!" << std::endl;

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');


    return EXIT_SUCCESS;
}