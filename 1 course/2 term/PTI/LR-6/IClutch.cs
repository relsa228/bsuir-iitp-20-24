namespace LR_6
{
    interface IClutch
    {
        void StartRevers(ITransmission transmission);
        void StartPark(ITransmission transmission);
        void StartDrive(ITransmission transmission);
    }
}