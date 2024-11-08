/*
 * CS106L Assignment 4: Weather Forecast
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 */

#include <algorithm>
#include <random>
#include <vector>
#include <iostream>


/* #### Please feel free to use these values, but don't change them! #### */
double kMaxTempRequirement = 5;
double uAvgTempRequirement = 60;

struct Forecast {
  double min_temp;
  double max_temp;
  double avg_temp;
};

Forecast compute_forecast(const std::vector<double>& dailyWeather) {
  // STUDENT TODO 1: return a forecast for the daily weather that is passed in.
  Forecast res;
  res.min_temp = *std::min_element(dailyWeather.begin(), dailyWeather.end()); //return iter
  res.max_temp = *std::max_element(dailyWeather.begin(), dailyWeather.end());

  res.avg_temp = std::accumulate(dailyWeather.begin(), dailyWeather.end(), 0.0)/dailyWeather.size();
  return res;
}

std::vector<Forecast> get_forecasts(const std::vector<std::vector<double>>& weatherData) {
  /*
   * STUDENT TODO 2: returns a vector of Forecast structs for the weatherData which contains
   * std::vector<double> which contain values for the weather on that day.
   */
  std::vector<Forecast> res(weatherData.size());

  // std::transform()  对范围内的元素应用函数并将结果存储到另一容器
  
  std::transform(weatherData.begin(), weatherData.end(), res.begin(), compute_forecast);
  return res;
}

std::vector<Forecast> get_filtered_data(const std::vector<Forecast>& forecastData) {
  // STUDENT TODO 3: return a vector with Forecasts filtered for days with specific weather.
  // std::remove_if 不删除元素，只是重排序元素，将被筛选出的放置末尾，
  // 并返回指向筛选出部分的begin()（不想被筛的end()）的迭代器；
  // std::erase 真正删除元素 
  auto copy = forecastData;
  auto new_end = std::remove_if(copy.begin(), copy.end(), [](Forecast data){  //lamda 要反着写
    return (data.max_temp-data.min_temp) <= kMaxTempRequirement || data.avg_temp < uAvgTempRequirement;
  });
  copy.erase(new_end, copy.end());
  return copy;
}


std::vector<Forecast> get_shuffled_data(const std::vector<Forecast>& forecastData) {
  // STUDENT TODO 4: Make use of a standard library algorithm to shuffle the data!
  auto copy = forecastData;
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(copy.begin(), copy.end(), g);
  return copy;
}

std::vector<Forecast> run_weather_pipeline(const std::vector<std::vector<double>>& weatherData) {
  // STUDENT TODO 5: Put your functions together to run the weather pipeline!
  auto forecasts = get_forecasts(weatherData);
  //std::cout << "Get Forecasts: \n";
  //for(auto elem:res)  std::cout << elem.min_temp << " " << elem.avg_temp << " " << elem.max_temp << std::endl;

  auto filteredForecasts = get_filtered_data(forecasts);
  // std::cout << "Get Filtered Forecasts: \n";
  // for(auto elem:filteredForecasts)  std::cout << elem.min_temp << " " << elem.avg_temp << " " << elem.max_temp << std::endl;
  
  auto shuffledForecasts = get_shuffled_data(filteredForecasts);


  return shuffledForecasts;
}

/* #### Please don't change this line! #### */
#include "utils.cpp"