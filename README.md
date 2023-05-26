<h1 align="center"> so_long - @42sp </h1>

<p align="center">:information_source: A small 2D Game made using the MiniLibX Graphics Library - Textures, sprites and tiles included. </p>
<p align="center"><a href="https://www.42sp.org.br/" target="_blank"><img src="https://img.shields.io/static/v1?label=&message=SP&color=000&style=for-the-badge&logo=42""></a></p>
<p align="center"><a href="https://github.com/augustobecker/so_long" target="_blank"><img align="center" alt="so_long" src="https://user-images.githubusercontent.com/81205527/179134510-48689e9e-f8e4-4165-be40-2e0ec8f5d60d.png"> </a></p>
<p align="center">123/100 :white_check_mark:</p>
<p align="center"><a href="https://github.com/augustobecker/SoLong/blob/main/READMES/README-ptbr.md" target="_blank"><img src="https://img.shields.io/badge/dispon%C3%ADvel%20tamb%C3%A9m%20em-PT--BR-yellow"></a></p>
<p align="center"><img src="https://user-images.githubusercontent.com/81205527/174392536-21619238-638a-4173-a77c-1b168c6c7898.png"> </p>

<p align="center">:magic_wand: Everything small is just a smaller version of something big</p>

## Index
* [What is so_long?](#what-is-so_long)
* [Requirements](#requirements)
* [How does it work?](#how-does-it-work)
	* [Maps](#maps)	
	* [Controls](#controls)
* [How do I test it?](#how-do-i-test-it)
* [42 Cursus](#42-cursus)
* [Author](#author)

<h2 align="center" id="what-is-so_long"> What is so_long? </h2>

The fifth project at 42 programming school.
It's the first graphical project in the <a href="https://github.com/augustobecker/42cursus">Cursus </a>, we can choose between 3 options - FdF, Fractol and so_long - that in general
cover different areas, but all 3 are graphical projects. The so_long consists of a top-down game, which we code from scratch using
the MiniLibx graphical library. It involves a series of validations from the map that is passed as argument,
checks to prevent memoy leaks, the game engineering, managing windows, events, sprites and maps.
	
<h2 align="center" id="requirements"> Requirements </h2>

<p  align="center"> :warning: The project must be written in accordance with the <a href="https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf" target="_blank">Norm</a> </p>
The Norm  is a programming standard that defines a set of rules to follow when writing code at 42. It applies to all C projects within the Common Core by default, and
to any project where it's specified. These are some of them:

    Each function must be maximum 25 lines, not counting the function's own curly brackets.
    
    Each line must be at most 80 columns wide, comments included.
    
    A function can take 4 named parameters maximum.
    
    You can't declare more than 5 variables per function.
    
    You're not allowed to use: for , do...while , switch , case ,  goto  ,
    ternary operators such as `?' and VLAs - Variable Length Arrays.
  The norminette (as we call the norm at 42) is in python and open source.
  
  Its repository is available at https://github.com/42School/norminette.
    
<h2 align="center" id="how-does-it-work"> How does it work? </h2>

You'll be able to play once you install the <a href="https://github.com/42Paris/minilibx-linux">MiniLibx</a> features or if you're using one of the machines at 42.

To play, first compile the project with make:

	make
	
In case you wanna play the bonus version:

	make bonus
	
So, run ./so_long followed by the map:
	
	./so_long assets/maps/valid/map2.ber	

For bonus:
	
	./so_long_bonus assets/maps/valid/bonus/map5.ber
	
<h3 id="maps" align="center"> Maps </h3>   
You can parse any kind of map, as long as it respects the below rules:

The map must be a .ber file.

And can only contain these characters:
    
| CHAR |	OBJECT   |
| --------- | ---------- |
| 1         |   Wall   |
| C	        | Coin |
| E	        |   Exit  |
| P         |   Player  |      
| 0         |   Floor     |
    
For bonus there's an extra character - which makes you lose once touch it.
    
| CHAR |	OBJECT   |
| --------- | ---------- |
| T         |   Toxic River  |


The map must be rectangular and surrounded by walls '1'.

The map must contain at least one exit, one collectible, and one starting position.

Check some examples in the folder /assets/maps.
	
As in assets/maps/valid/map2.ber:

<img src="https://user-images.githubusercontent.com/81205527/163024984-1ff511c1-17d2-4eef-8d97-90cc8a884c73.png">
This .ber file generates this map:
    
    
<img src="https://user-images.githubusercontent.com/81205527/174420150-0ee15e42-c7c3-4854-936b-fffaf13683c2.png">
	
<h3 id="controls" align="center"> Controls </h3>   
    
| KEY |	OBJECT   |
| --------- | ---------- |
| W or ⬆️        |    Move up   |
| A	or ⬅️        |    Move left |
| S	or ⬇️     |    Move down   |
| D or ➡️       |   Move para right|      
| Q or Esc      |   Close the game     | 
    
    
Use WASD or arrow keys to move.
	
	
After getting all the coin bags, the exit opens and you can escape downstairs.
	
You can close the game by Clicking on the red cross on the window’s frame, or pressing Q or Esc.
	
<h2 align="center" id="how-do-i-test-it"> How do I test it? </h2>  

To test the game itself it's recommendable to run it with some different maps and try things like:

Running into a wall and see if you're blocked or if the movements counter increase while you're stucked.

Go to the exit withou collecting all the coins.

Go through the same path at least one time.

Try to move with the arrow keys and with WASD.

Check if the window closes when clicking the red cross on window's frame, same with Esc or Q.

Try to minimize the window and open it again.

Run the project with Valgrind to see if there's any memory leak.

To test some map validations as
No map, missing argv, multiple argv, invalid extension, map with an empty line, invalid map parameter
missing W parameter, missing C parameter, missing E parameter, missing P parameter, extra P parameter
I created my own [Tester](https://github.com/augustobecker/so_long_tester).

To test the code in this repo Clone this repo and cd into it:
```
git clone https://github.com/augustobecker/so_long

cd so_long/
```
Now, clone the Tester

```
git clone https://github.com/augustobecker/so_long_tester
```

Go into the test folder and run with make:

```
cd so_long_tester
make
```

If you did everything correctly you should see something like this

![image](https://user-images.githubusercontent.com/81205527/179400332-9e80f631-7d46-464b-a0eb-e481b48ad6b4.png)

<h2 align="center" id="42-cursus"> 42 Cursus </h2>
	
42 is a global education initiative that proposes a new way of learning technology: no teachers, no classrooms,
students learning from their fellow students (peer to peer learning),
with a methodology that develops both computing and life skills.
Not to mention that it's completely free of charge and open to all with no prerequisites.

Admissions at 42 are unlike other colleges. We use a merit-based admission process.
The final step of the admission is the Piscine - This is part of the admissions process and 
requires 4 weeks of intensive and immersive coding. No prior coding experience is necessary at all.
	
You can check more about the admission process on the 42sp website: https://www.42sp.org.br or on my github repository: <a href="">42 Piscine</a>

To see other projects developed by me at 42, click here: <a href="https://github.com/augustobecker/42cursus">42 Cursus </a>
	
<h2  align="center" id="author">Author</h2>
<div align="center">
	<div>
	<img height="222em" src="https://user-images.githubusercontent.com/81205527/174709160-f4bc029d-b667-469b-b2a7-4e036f1c5349.png">
	</div>
	<div>
		<strong> Augusto Becker | acesar-l | 🇧🇷👨‍🚀</strong>
	
:wave: How to reach me:
    	</div> 
    	<div>
  	<a href="https://www.linkedin.com/in/augusto-becker/" target="_blank"><img align="center" alt="LinkedIn" height="60" src="https://user-images.githubusercontent.com/81205527/157161849-01a9df02-bf32-45be-add4-122bc40b48cf.png"></a>
	<a href="https://www.instagram.com/augusto.becker/" target="_blank"><img align="center" alt="Instagram" height="60" src="https://user-images.githubusercontent.com/81205527/157161841-19ec3ab2-2c8f-4ec0-8b9d-3cd885256098.png"></a>
	<a href = "mailto:augustobecker.dev@gmail.com"> <img align="center" alt="Gmail - augustobecker.dev@gmail.com" height="60" src="https://user-images.githubusercontent.com/81205527/157161831-eb9dffee-404b-4ffe-b0af-34671219f7fb.png"></a>
	<a href="https://discord.gg/3kxYkBRxUy" target="_blank"><img align="center" alt="Discord - beckerzz#3614" height="60" src="https://user-images.githubusercontent.com/81205527/157161820-de88dc63-61a3-4c9f-9445-07ac98bf0bc2.png"></a>
	</div>
</div>
