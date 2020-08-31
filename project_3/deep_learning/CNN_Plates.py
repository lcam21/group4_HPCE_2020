from __future__ import absolute_import, division, print_function, unicode_literals

import tensorflow as tf
import numpy as np
import cv2
import pickle
import pandas as pd
import json
import matplotlib.pyplot as plt
from skimage.color import rgb2gray
from tensorflow import keras

from PIL import Image
from skimage.transform import resize

from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Activation, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D

IMG_SIZE=128

def load_first_model():
	#Modelo secuencial, se añaden los layers de la CNN
    model = Sequential()
    model.add(Conv2D(256, (3, 3), input_shape=(128, 128, 3)))
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))

    model.add(Conv2D(256, (3, 3)))
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2, 2)))

    model.add(Flatten())

    model.add(Dense(64))

    model.add(Dense(1))
    model.add(Activation('sigmoid'))

    checkpoint_path = "/home/verny/projecto3/jetson/modelo_verny/cp.ckpt"

    model.load_weights(checkpoint_path)
    return model

def load_second_model():
    # Modelo secuencial, se añaden los layers de la CNN
    model = Sequential()
    model.add(Conv2D(28, kernel_size=(3,3), input_shape=input_shape))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Flatten()) # 
    model.add(Dense(128, activation=tf.nn.relu))
    model.add(Dropout(0.2))
    model.add(Dense(10,activation=tf.nn.softmax))
    checkpoint_path = "/home/verny/projecto3/jetson/modelo_verny/Model_Verny2.ckpt"

    model.load_weights(checkpoint_path)
    return model

def get_image_in_format(filepath):      
    im = np.array(Image.open(filepath))
    print(im.shape)
    new_array = cv2.resize(im, (IMG_SIZE, IMG_SIZE))
    return new_array.reshape(-1, IMG_SIZE, IMG_SIZE, 3) 

def get_image(filepath):
    im = np.array(Image.open(filepath))
    return im
def get_second_model_evaluation(image_original,model):
    img_rows, img_cols = 28, 28
    image_original_gray = rgb2gray(image_original)
    image_original_gray_res = resize(image_original_gray, (28,28))

    image_index = 3333
    plt.imshow(image_original_gray_res.reshape(28, 28),cmap='Greys')
    pred = model.predict(image_original_gray_res.reshape(1, img_rows, img_cols, 1))
    
    dia_semana = 0 # El dia es lunes
    pred = model.predict(image_original_gray_res.reshape(1, img_rows, img_cols, 1))

    if pred.argmax() == 0:
        if dia_semana == 0:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 1:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
    if pred.argmax() == 1:
        if dia_semana == 0:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 1:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
            
    if pred.argmax() == 2:
        if dia_semana == 2:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 3:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")      
    if pred.argmax() == 3:
        if dia_semana == 2:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 3:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
            
    if pred.argmax() == 4:
        if dia_semana == 4:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 5:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
    if pred.argmax() == 5:
        if dia_semana == 4:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 5:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")     
            
    if pred.argmax() == 6:
        if dia_semana == 6:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 7:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
    if pred.argmax() == 7:
        if dia_semana == 6:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 7:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
            
    if pred.argmax() == 8:
        if dia_semana == 8:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 9:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
    if pred.argmax() == 9:
        if dia_semana == 8:
            print("El carro no cumple con la restriccion vehicular")
        elif dia_semana == 9:
            print("El carro no cumple con la restriccion vehicular")
        else:
            print("El carro cumple con la restriccion vehicular")
            
    plt.imshow(image_original_gray_res.reshape(28, 28),cmap='Greys')    
    return pred.argmax()
def main():
    first_model=load_first_model()
    second_model=load_second_model()
    #metodo estatico para agregar imagen
    plate_image=get_image_in_format('/home/verny/projecto3/model_inputs/plate1.jpeg'
    raw_image=get_image('/home/verny/projecto3/model_inputs/plate1.jpeg')
    prediction_upon_image_captured=first_model.predict(plate_image)
    if prediction_upon_image_captured==0:
        print("Es una placa, hora de buscar la ultima letra")
        #manera de recortar la imagen para obtener la ultima posicion de la placa
        x_point_top = raw_image.shape[1]/8*6
        y_point_top = 0
        x_point_bot = raw_image.shape[1]
        y_point_bot = raw_image.shape[0]
        plateImage = Image.fromarray(raw_image).crop((x_point_top, y_point_top, x_point_bot, y_point_bot))
        fig, ax = plt.subplots(1, 1, constrained_layout=True)
        print(type(plateImage))

    else:
        print("No es placa")
       
    
  
if __name__== "__main__":
  main()