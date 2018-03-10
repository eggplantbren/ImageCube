ImageCube
=========

(c) 2018 Brendon J. Brewer

LICENSE: GNU General Public License v3.


Instructions
============

## Download and compile

```
git clone --recursive https://github.com/eggplantbren/ImageCube
cd ImageCube
make
```

You'll also need to install the DNest4 Python package
(see [here](https://github.com/eggplantbren/DNest4) for instructions).

## Generate the example data

There is an example dataset, and I've only implemented very simplistic and
inflexible inference assumptions so far. To generate the example dataset,
do this:

```
cd python
python generate_example_data.py
cd ..
```

If you have ffmpeg installed this will also generate a video
that you can watch, in python/images/movie.mkv. If you don't have ffmpeg
you'll still get all the frames as .png files,
and the data file will still be generated, despite the error message.

## Running the analysis on the example data

To do the analysis on the example data using 8 threads (recommended), use

```
./main -t 8
```

The program will run and you will see
DNest4 output. It's quite slow but not the worst I've seen. There are also some
potential speedup techniques that I haven't implemented yet.

## Postprocessing

Once it's been running for a while, you can do

```
python showresults.py
```

which will show the usual DNest4 plots and (once you've closed those)
an image of the residuals.

## TODO

Lots of stuff: make the assumptions more realistic and flexible, use a more
convenient data format including metadata (e.g., using FITS or YAML),
provide useful output (i.e., parameter estimates, not just the residuals).

