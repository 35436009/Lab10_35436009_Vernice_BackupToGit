#ifndef MONTHLYSUMMARY_H
#define MONTHLYSUMMARY_H

/**
 * @class MonthlySummary
 * @brief Stores the computed statistics for one month of one year.
 *
 * This class is a simple data container used by UtilityStats and BST.
 *
 * @author Vernice Foong
 * @version 01
 */
class MonthlySummary
{
public:
    /**
     * @brief Default constructor.
     */
    MonthlySummary();

    /**
     * @brief Gets the year.
     * @return Year value.
     */
    int GetYear() const;

    /**
     * @brief Sets the year.
     * @param year Year value.
     */
    void SetYear(int year);

    /**
     * @brief Gets the month.
     * @return Month value.
     */
    int GetMonth() const;

    /**
     * @brief Sets the month.
     * @param month Month value.
     */
    void SetMonth(int month);

    /**
     * @brief Gets the mean wind speed.
     * @return Mean wind speed.
     */
    float GetMeanSpeed() const;

    /**
     * @brief Sets the mean wind speed.
     * @param value Mean wind speed.
     */
    void SetMeanSpeed(float value);

    /**
     * @brief Gets the wind speed standard deviation.
     * @return Wind speed standard deviation.
     */
    float GetSpeedStDev() const;

    /**
     * @brief Sets the wind speed standard deviation.
     * @param value Wind speed standard deviation.
     */
    void SetSpeedStDev(float value);

    /**
     * @brief Gets the wind speed mean absolute deviation.
     * @return Wind speed MAD.
     */
    float GetSpeedMad() const;

    /**
     * @brief Sets the wind speed mean absolute deviation.
     * @param value Wind speed MAD.
     */
    void SetSpeedMad(float value);

    /**
     * @brief Gets the mean temperature.
     * @return Mean temperature.
     */
    float GetMeanTemp() const;

    /**
     * @brief Sets the mean temperature.
     * @param value Mean temperature.
     */
    void SetMeanTemp(float value);

    /**
     * @brief Gets the temperature standard deviation.
     * @return Temperature standard deviation.
     */
    float GetTempStDev() const;

    /**
     * @brief Sets the temperature standard deviation.
     * @param value Temperature standard deviation.
     */
    void SetTempStDev(float value);

    /**
     * @brief Gets the temperature mean absolute deviation.
     * @return Temperature MAD.
     */
    float GetTempMad() const;

    /**
     * @brief Sets the temperature mean absolute deviation.
     * @param value Temperature MAD.
     */
    void SetTempMad(float value);

    /**
     * @brief Gets the total solar radiation.
     * @return Solar total.
     */
    double GetSolarTotal() const;

    /**
     * @brief Sets the total solar radiation.
     * @param value Solar total.
     */
    void SetSolarTotal(double value);

    /**
     * @brief Gets the SPCC for wind speed and temperature.
     * @return SPCC value.
     */
    double GetSPCCSpeedTemp() const;

    /**
     * @brief Sets the SPCC for wind speed and temperature.
     * @param value SPCC value.
     */
    void SetSPCCSpeedTemp(double value);

    /**
     * @brief Gets the SPCC for wind speed and solar radiation.
     * @return SPCC value.
     */
    double GetSPCCSpeedSolar() const;

    /**
     * @brief Sets the SPCC for wind speed and solar radiation.
     * @param value SPCC value.
     */
    void SetSPCCSpeedSolar(double value);

    /**
     * @brief Gets the SPCC for temperature and solar radiation.
     * @return SPCC value.
     */
    double GetSPCCTempSolar() const;

    /**
     * @brief Sets the SPCC for temperature and solar radiation.
     * @param value SPCC value.
     */
    void SetSPCCTempSolar(double value);

    /**
     * @brief Checks whether the month has usable data.
     * @return True if usable data exists, otherwise false.
     */
    bool HasData() const;

    /**
     * @brief Sets whether the month has usable data.
     * @param value True if usable data exists, otherwise false.
     */
    void SetHasData(bool value);

    /**
     * @brief Compares summaries by year and month.
     * @param other Another summary.
     * @return True if this summary is earlier than other.
     */
    bool operator<(const MonthlySummary& other) const;

    /**
     * @brief Checks whether two summaries have the same year and month.
     * @param other Another summary.
     * @return True if both summaries match.
     */
    bool operator==(const MonthlySummary& other) const;

    /**
     * @brief Compares summaries by year and month.
     * @param other Another summary.
     * @return True if this summary is later than other.
     */
    bool operator>(const MonthlySummary& other) const;

private:
    int m_year;
    int m_month;
    float m_meanSpeed;
    float m_speedStDev;
    float m_speedMad;
    float m_meanTemp;
    float m_tempStDev;
    float m_tempMad;
    double m_solarTotal;
    double m_spccSpeedTemp;
    double m_spccSpeedSolar;
    double m_spccTempSolar;
    bool m_hasData;
};

#endif
