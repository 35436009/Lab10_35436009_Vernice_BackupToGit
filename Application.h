#ifndef APPLICATION_H
#define APPLICATION_H

#include "WeatherLog.h"

/**
 * @class Application
 * @brief Controls the menu system and program execution.
 *
 * Responsibilities:
 * - Display menu
 * - Handle user input
 * - Call statistics functions
 * - Write output file
 *
 * @author Vernice Foong
 * @version 04
 */
class Application
{
public:
    /**
     * @brief Constructor that uses the loaded WeatherLog.
     *
     * @param log Reference to the weather log.
     */
    Application(WeatherLog& log);

    /**
     * @brief Starts the program and controls the main menu loop.
     */
    void Run();

private:
    WeatherLog& m_log;  // Reference to the loaded WeatherLog.

    /**
     * @brief Displays the main menu options to the user.
     */
    void DisplayMenu() const;

    /**
     * @brief Reads an integer input from the user.
     *
     * @return The integer entered by the user.
     */
    int ReadInt() const;

    /**
     * @brief Returns the English name of a given month.
     *
     * @param month Month number (1-12).
     * @return Pointer to a constant month name string.
     */
    const char* GetMonthName(int month) const;

    /**
     * @brief Menu Option 1:
     * Computes and displays wind speed mean and sample standard deviation
     * for a specified month and year.
     */
    void DoOption1();

    /**
     * @brief Menu Option 2:
     * Computes and displays temperature mean and sample standard deviation
     * for each month of a specified year.
     */
    void DoOption2();

    /**
     * @brief Menu Option 3:
     * Computes and displays sample Pearson correlation coefficients for
     * wind speed, temperature, and solar radiation for a specified month.
     */
    void DoOption3();

    /**
     * @brief Menu Option 4:
     * Generates WindTempSolar.csv containing monthly wind, temperature,
     * and solar statistics for a specified year.
     */
    void DoOption4();
};

#endif
