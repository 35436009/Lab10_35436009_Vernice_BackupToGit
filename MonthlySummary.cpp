#include "MonthlySummary.h"

// Default constructor.
MonthlySummary::MonthlySummary()
{
    m_year = 0;
    m_month = 0;
    m_meanSpeed = 0.0f;
    m_speedStDev = 0.0f;
    m_speedMad = 0.0f;
    m_meanTemp = 0.0f;
    m_tempStDev = 0.0f;
    m_tempMad = 0.0f;
    m_solarTotal = 0.0;
    m_spccSpeedTemp = 0.0;
    m_spccSpeedSolar = 0.0;
    m_spccTempSolar = 0.0;
    m_hasData = false;
}

// Gets the year.
int MonthlySummary::GetYear() const
{
    return m_year;
}

// Sets the year.
void MonthlySummary::SetYear(int year)
{
    m_year = year;
}

// Gets the month.
int MonthlySummary::GetMonth() const
{
    return m_month;
}

// Sets the month.
void MonthlySummary::SetMonth(int month)
{
    m_month = month;
}

// Gets the mean wind speed.
float MonthlySummary::GetMeanSpeed() const
{
    return m_meanSpeed;
}

// Sets the mean wind speed.
void MonthlySummary::SetMeanSpeed(float value)
{
    m_meanSpeed = value;
}

// Gets the wind speed standard deviation.
float MonthlySummary::GetSpeedStDev() const
{
    return m_speedStDev;
}

// Sets the wind speed standard deviation.
void MonthlySummary::SetSpeedStDev(float value)
{
    m_speedStDev = value;
}

// Gets the wind speed MAD.
float MonthlySummary::GetSpeedMad() const
{
    return m_speedMad;
}

// Sets the wind speed MAD.
void MonthlySummary::SetSpeedMad(float value)
{
    m_speedMad = value;
}

// Gets the mean temperature.
float MonthlySummary::GetMeanTemp() const
{
    return m_meanTemp;
}

// Sets the mean temperature.
void MonthlySummary::SetMeanTemp(float value)
{
    m_meanTemp = value;
}

// Gets the temperature standard deviation.
float MonthlySummary::GetTempStDev() const
{
    return m_tempStDev;
}

// Sets the temperature standard deviation.
void MonthlySummary::SetTempStDev(float value)
{
    m_tempStDev = value;
}

// Gets the temperature MAD.
float MonthlySummary::GetTempMad() const
{
    return m_tempMad;
}

// Sets the temperature MAD.
void MonthlySummary::SetTempMad(float value)
{
    m_tempMad = value;
}

// Gets the total solar radiation.
double MonthlySummary::GetSolarTotal() const
{
    return m_solarTotal;
}

// Sets the total solar radiation.
void MonthlySummary::SetSolarTotal(double value)
{
    m_solarTotal = value;
}

// Gets the SPCC for wind speed and temperature.
double MonthlySummary::GetSPCCSpeedTemp() const
{
    return m_spccSpeedTemp;
}

// Sets the SPCC for wind speed and temperature.
void MonthlySummary::SetSPCCSpeedTemp(double value)
{
    m_spccSpeedTemp = value;
}

// Gets the SPCC for wind speed and solar radiation.
double MonthlySummary::GetSPCCSpeedSolar() const
{
    return m_spccSpeedSolar;
}

// Sets the SPCC for wind speed and solar radiation.
void MonthlySummary::SetSPCCSpeedSolar(double value)
{
    m_spccSpeedSolar = value;
}

// Gets the SPCC for temperature and solar radiation.
double MonthlySummary::GetSPCCTempSolar() const
{
    return m_spccTempSolar;
}

// Sets the SPCC for temperature and solar radiation.
void MonthlySummary::SetSPCCTempSolar(double value)
{
    m_spccTempSolar = value;
}

// Checks whether the month has usable data.
bool MonthlySummary::HasData() const
{
    return m_hasData;
}

// Sets whether the month has usable data.
void MonthlySummary::SetHasData(bool value)
{
    m_hasData = value;
}

// Compares summaries by year and month for ordering.
bool MonthlySummary::operator<(const MonthlySummary& other) const
{
    if (m_year < other.m_year)
    {
        return true;
    }
    else if (m_year > other.m_year)
    {
        return false;
    }
    else
    {
        if (m_month < other.m_month)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Checks whether two summaries have the same year and month for equality.
bool MonthlySummary::operator==(const MonthlySummary& other) const
{
    if (m_year == other.m_year)
    {
        if (m_month == other.m_month)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Compares summaries by year and month for search support.
bool MonthlySummary::operator>(const MonthlySummary& other) const
{
    if (m_year > other.m_year)
    {
        return true;
    }
    else if (m_year < other.m_year)
    {
        return false;
    }
    else
    {
        if (m_month > other.m_month)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}