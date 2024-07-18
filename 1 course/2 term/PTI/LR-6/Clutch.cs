namespace LR_6
{ 
    class Clutch: IClutch
    {
        public void StartRevers(ITransmission transmission)
        {
            transmission.Revers();
        }

        public void StartPark(ITransmission transmission)
        {
            transmission.Park();
        }

        public void StartDrive(ITransmission transmission)
        {
            transmission.Drive();
        }
    }
}