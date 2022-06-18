class Pump{
    public:
        Pump();
        void start();
        void stop();
        void setPumpDuration(int duration);
    private:
        int duration;
};

