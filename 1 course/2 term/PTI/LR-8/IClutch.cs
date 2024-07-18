namespace LR_8
{
    interface IClutch
    {
        void StartRevers(ITransmission transmission);
        void StartPark(ITransmission transmission);
        void StartDrive(ITransmission transmission);
    }
}