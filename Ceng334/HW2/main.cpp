#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <queue>
#include "monitor.h"
#include "helper.h"
#include "WriteOutput.h"
#define BIGGER(left, right) \
    ((left).tv_sec > (right).tv_sec || ((left).tv_sec == (right).tv_sec && (left).tv_nsec > (right).tv_nsec))
using namespace std;
//3170 3550 3540
vector<vector<int>> narrowBridges;
vector<vector<int>> ferries;
vector<vector<int>> crossRoads;
int nbNum;
int fNum;
int crNum;
int carNum;
int travelTimeBetweenConnectors;

struct Car {
    int id;
    int travelTime;
    vector<vector<string>> path; // (from, to) pairs representing connectors
};




class NarrowBridge: public Monitor {   // inherit from Monitor
	queue<int> carIds[2];
	vector<int> waitlist;
	pthread_mutex_t  mute;
	Condition direction, waitpass, passedbeforecond, sira, uyu;
	struct timespec desiredTime;
	int curDir = 0;
	int passing = 0;
	bool timeFlag[2] = {false, false};
	pthread_cond_t siraa[2], karsi[2], karsi2;
	public:
		NarrowBridge() : direction(this) , waitpass(this), passedbeforecond(this), sira(this), uyu(this){
			pthread_cond_init(&karsi[0], NULL);
			pthread_cond_init(&karsi[1], NULL);
			pthread_cond_init(&karsi2, NULL);
			pthread_mutex_init(&mute, NULL);
			pthread_cond_init(&siraa[0], NULL) ;
			pthread_cond_init(&siraa[1], NULL) ;
		}   // pass "this" to cv constructors
		void PassPassage(int carId, int carDir, int rId) {
			WriteOutput(carId, 'N',rId,ARRIVE);
			//cout<<carId <<" girmeyi bekliyor\n";
			pthread_mutex_lock(&mute);
			//cout<< "girişi " << carId<< "koydu"<<endl;
			carIds[carDir].push(carId);
		begin:

				if (curDir == carDir) {//same direction
					//If one is passing
					if (carIds[carDir].front() == carId) { //First car
						//cout<< carId<< " if ifte\n";
						if (passing >0) {
							//cout<< carId << "passdelayde uyudu"<<endl;
							pthread_mutex_unlock(&mute);
							//cout<< carId << " mutexi saldı"<<endl;
							sleep_milli(PASS_DELAY);
							pthread_mutex_lock(&mute);
							//cout<< "mutex " << carId<< "'nin"<<endl;
							//cout<< carId << " pass delayi bekledi ve kitledi\n";
						}
						if(curDir != carDir) goto begin;
						carIds[carDir].pop();
						passing++;
						
						//cout<< carId <<" notifies sira"<< endl;
						pthread_cond_broadcast(&siraa[carDir]);
						WriteOutput(carId, 'N', rId, START_PASSING);
						pthread_cond_broadcast(&karsi[carDir]);
						//cout << carId<< " mutexi saldı"<<endl;
						//cout << carId<< " waiting and gave up mutex"<<endl;
						pthread_mutex_unlock(&mute);
						
						sleep_milli(narrowBridges[rId][0]);
						pthread_mutex_lock(&mute);
						passing--;
						//cout<< "mutex " << carId<< "'nin"<<endl;
						//cout<< carId << " geçmeyi bekledi ve kitledi\n";
						//pthread_cond_broadcast(&karsi2);
						WriteOutput(carId, 'N', rId, FINISH_PASSING);
						//sira.notifyAll();
						if(passing == 0) pthread_cond_broadcast(&karsi2);
						
						if (carIds[curDir].size() == 0 && passing == 0) { //bu yol bitti diğerine geç

							curDir = 1 - curDir; //switch lane
							//cout<<"Geçerli yön a:"<< curDir <<endl;
							//cout<<"aaaaaaaaaa\n";
							pthread_cond_broadcast(&siraa[curDir]);
							pthread_cond_broadcast(&karsi[curDir]);
							pthread_cond_broadcast(&karsi2);
						}
						//cout << "changed\n";
					}

					else {
						//cout<< carId<< " if elsede\n";
						pthread_cond_wait(&siraa[carDir], &mute);
						goto begin;
					}
				}
				else{ //yanlis yol
					//cout<< "yanlis yol\n";
					
					if (carIds[curDir].size() == 0 && passing == 0) { //diğer yol boş
							//cout<< carId<< " else ifte\n";
							curDir = 1 - curDir; //switch lane
							//cout<<"Geçerli yön b:"<< curDir <<endl;
							pthread_cond_broadcast(&siraa[carDir]);
							pthread_cond_broadcast(&karsi[carDir]);
							pthread_cond_broadcast(&karsi2);
					}

					else{
						
						if(!timeFlag[carDir]){
							//cout<< carId<< " else else flagde\n";
							timeFlag[carDir] = !timeFlag[carDir];
							struct timespec curTime;
							clock_gettime(CLOCK_REALTIME, &curTime);
							//cout<<"yön değişme başladı"<<endl;
							curTime.tv_nsec+=(narrowBridges[rId][1]%1000)*1000000;
							curTime.tv_sec +=(narrowBridges[rId][1]/1000);
							if(curTime.tv_nsec >= 1000000000){
								curTime.tv_sec++;
								curTime.tv_nsec-=1000000000;
							}
							
							pthread_cond_timedwait(&karsi[carDir], &mute, &curTime);
							if(curDir != carDir){
							curDir = (curDir+1)%2;
							//cout<<"Geçerli yön c:"<< curDir <<endl;
							//cout<<"Yön değişti\n";
							}
							if(passing != 0)pthread_cond_wait(&karsi2,&mute);
							pthread_cond_broadcast(&siraa[carDir]);
							timeFlag[carDir] = !timeFlag[carDir];
						}
						
						else{
							//cout<< carId<< " else elsede\n";
							pthread_cond_wait(&siraa[carDir], &mute);
						}
					}

					goto begin;
				}

				pthread_mutex_unlock(&mute);

		}
			
			
			
			// no need to unlock here, destructor of macro variable does it

};






class Ferry: public Monitor {   // inherit from Monitor
    pthread_cond_t doldu[2];    // condition varibles
    pthread_mutex_t  mute;
    pthread_cond_t timeWait[2];
    int kita[2] = {0,0};
	bool flag[2] = { false, false };
    
	public:
		Ferry() {  
		    pthread_cond_init(&doldu[0], NULL);
		    pthread_cond_init(&doldu[1], NULL);
		    pthread_cond_init(&timeWait[1], NULL);
		    pthread_cond_init(&timeWait[0], NULL);
			pthread_mutex_init(&mute, NULL);
		}
		void PassPassage(int carId, int carDir, int rId) {
			pthread_mutex_lock(&mute);
			//cout << flag[carId] << endl;
			//cout<<"mutex "<< carId <<" nin\n";
			if(kita[carDir] == ferries[rId][2]){
				kita[carDir] = 0;
				pthread_mutex_unlock(&mute);
				sleep_milli(1);
				pthread_mutex_lock(&mute);
			
			}
			kita[carDir]++;
			//cout<<carId<<" kitayi "<<kita[carDir]<<" yapti"<<endl;
			if(kita[carDir] == ferries[rId][2]) {
				//cout <<carId<< " a\n";
				WriteOutput(carId, 'F', rId, START_PASSING);
				pthread_cond_broadcast(&doldu[carDir]);
				pthread_cond_signal(&timeWait[carDir]);
				pthread_mutex_unlock(&mute);
				sleep_milli(ferries[rId][0]);
				pthread_mutex_lock(&mute);
				WriteOutput(carId, 'F', rId, FINISH_PASSING);
				pthread_mutex_unlock(&mute);
				
			}
			else{
				if(kita[carDir] == 1) {
					//cout <<carId<< " b\n";
					//cout<<"curullah\n";
					flag[carDir] = true;
					//cout << flag[carId] << endl;
					struct timespec curTime;
					clock_gettime(CLOCK_REALTIME, &curTime);
					
					curTime.tv_nsec+=(ferries[rId][1]%1000)*1000000;
					curTime.tv_sec +=(ferries[rId][1]/1000);
					if(curTime.tv_nsec >= 1000000000){
						curTime.tv_sec++;
						curTime.tv_nsec-=1000000000;
					}
					pthread_cond_timedwait(&timeWait[carDir], &mute, &curTime);
					kita[carDir] = 0;
					flag[carDir] = false;
					pthread_cond_broadcast(&doldu[carDir]);
					goto finish;
				}
				else{
					//cout <<carId<< " c\n";
					//cout<<"curullah1\n";
					pthread_cond_wait(&doldu[carDir], &mute);
					finish:
						WriteOutput(carId, 'F', rId, START_PASSING);
						pthread_mutex_unlock(&mute);
						sleep_milli(ferries[rId][0]);
						pthread_mutex_lock(&mute);
						WriteOutput(carId, 'F', rId, FINISH_PASSING);
						pthread_mutex_unlock(&mute);
				}
			}
 
		} 


};



class CrossRoad: public Monitor {   // inherit from Monitor
    queue<int> carIds[4];
	pthread_mutex_t  mute;
	struct timespec desiredTime;
	int curDir = 0;
	int passing = 0;
	bool kilit = false, changed = false, a = false, degisti = false;
	bool timeFlag[4] = {false, false, false, false};
	pthread_cond_t siraa[4], karsi[4], karsi2[4];
	public:
		CrossRoad() {
			pthread_cond_init(&karsi[0], NULL);
			pthread_cond_init(&karsi[1], NULL);
			pthread_cond_init(&karsi[2], NULL);
			pthread_cond_init(&karsi[3], NULL);
			pthread_cond_init(&karsi2[0], NULL);
			pthread_cond_init(&karsi2[1], NULL);
			pthread_cond_init(&karsi2[2], NULL);
			pthread_cond_init(&karsi2[3], NULL);
			pthread_mutex_init(&mute, NULL);
			pthread_cond_init(&siraa[0], NULL) ;
			pthread_cond_init(&siraa[1], NULL) ;
			pthread_cond_init(&siraa[2], NULL);
			pthread_cond_init(&siraa[3], NULL);
		}   // pass "this" to cv constructors
		void PassPassage(int carId, int carDir, int rId) {
			
			WriteOutput(carId, 'C',rId,ARRIVE);
			//cout<<"curdir ="<<curDir<<endl;
			//cout<<carId <<" girmeyi bekliyor\n";
			pthread_mutex_lock(&mute);
			//cout<< "girişi " << carId<< "koydu"<<endl;
			carIds[carDir].push(carId);
		begin:	
				//a = false;
				//cout<<"Başta araba yönü: "<<carDir<<endl; 
				if (curDir == carDir) {//same direction
					//If one is passing
					if (carIds[carDir].front() == carId) { //First car
						//acout<< carId<< " if ifte\n";
						if (passing >0) {
							//cout<< carId << "passdelayde uyudu"<<endl;
							pthread_mutex_unlock(&mute);
							//cout<< carId << " mutexi saldı"<<endl;
							sleep_milli(PASS_DELAY);
							pthread_mutex_lock(&mute);
							//cout<< "mutex " << carId<< "'nin"<<endl;
							//cout<< carId << " pass delayi bekledi ve kitledi\n";
						}
						//cout<< "carId Curdir "<<carId<<" "<<curDir<<endl;
						if(curDir != carDir) goto begin;
						carIds[carDir].pop();
						passing++;
						
						//cout<< carId <<" notifies sira"<< endl;
						pthread_cond_broadcast(&siraa[carDir]);
						WriteOutput(carId, 'C', rId, START_PASSING);
						pthread_cond_broadcast(&karsi[carDir]);
						//cout << carId<< " mutexi saldı"<<endl;
						//cout << carId<< " waiting and gave up mutex"<<endl;
						pthread_mutex_unlock(&mute);
						
						sleep_milli(crossRoads[rId][0]);
						pthread_mutex_lock(&mute);
						passing--;
						//cout<< "mutex " << carId<< "'nin"<<endl;
						//cout<< carId << " geçmeyi bekledi ve kitledi\n";
						
						WriteOutput(carId, 'C', rId, FINISH_PASSING);
						if(passing == 0) pthread_cond_broadcast(&karsi2[carDir]);
						//cout<<carId<<" de curDir = "<<curDir<<endl;
						if (carIds[curDir].size() == 0 && passing == 0 || curDir != carDir) { //bu yol bitti diğerine geç
							if(changed != true){
								for (int i= 0, cur = curDir ; i<4; i++){
									if(carIds[(cur+i+1)%4].size()!=0){
										curDir = (cur + i + 1)%4;
										break;
										degisti = true;
									}
									
								}
							}
							
							if(passing == 0 || curDir != carDir) pthread_cond_broadcast(&karsi2[curDir]);
								//switch lane
							//cout<<"Geçerli yön a:"<< curDir <<endl;
							//cout<<"aaaaaaaaaa\n";
							pthread_cond_broadcast(&siraa[curDir]);
							pthread_cond_broadcast(&karsi[curDir]);
							pthread_cond_broadcast(&karsi2[curDir]);
						}
						//cout << "changed\n";
					}

					else {
						//cout<< carId<< " if elsede\n";
						pthread_cond_wait(&siraa[carDir], &mute);
						goto begin;
					}
				}
				else{ //yanlis yol
					//cout<< "yanlis yol\n";
					
					if (carIds[curDir].size() == 0 && passing == 0) { //diğer yol boş
							//cout<<carId<<" else ifte\n";
							int cur = curDir;
							for (int i= 0 ; i<4; i++){
								int t = (cur + i +1)%4;

								if(carIds[(cur+i+1)%4].size()!=0){
									curDir = (cur + i + 1)%4;
									break;
								}
								degisti = true;
							}
							
							if(curDir != carDir) pthread_cond_wait(&karsi[carDir], &mute);
							
							pthread_cond_broadcast(&siraa[curDir]);
							pthread_cond_broadcast(&karsi[curDir]);
							pthread_cond_broadcast(&karsi2[curDir]);
					}

					else{
						
						if(!timeFlag[carDir]){
							aga:
							degisti = false;
							//cout<< carId<< " else else flagde\n";
							timeFlag[carDir] = !timeFlag[carDir];
							struct timespec curTime;
							clock_gettime(CLOCK_REALTIME, &curTime);
							//cout<<"yön değişme başladı"<<endl;
							curTime.tv_nsec+=(crossRoads[rId][1]%1000)*1000000;
							curTime.tv_sec +=(crossRoads[rId][1]/1000);
							if(curTime.tv_nsec >= 1000000000){
								curTime.tv_sec++;
								curTime.tv_nsec-=1000000000;
							}
							
							pthread_cond_timedwait(&karsi[carDir], &mute, &curTime);
							if (degisti == true && carDir != curDir) goto aga;
							if(a == true) 
							{
								pthread_mutex_unlock(&mute);
								sleep_milli(2);
								pthread_mutex_lock(&mute);
								a = false;
								goto begin;
							}
							a = false;
							if(carDir == curDir) {
							changed = true;
							goto assa;
							}
							if(kilit == false && changed == false){
								kilit = true;
								int cur = curDir;
								for (int i= 0 ; i<4; i++){
									int t = (cur + i +1)%4;

									if(carIds[(cur+i+1)%4].size()!=0){
										curDir = (cur + i + 1)%4;
										break;
									}
								}
								//cout<< carId<< " made curDir"<<curDir<<endl;
								pthread_mutex_unlock(&mute);
								sleep_milli(2);
								pthread_mutex_lock(&mute);
								changed = true;
								
							}
							assa:
							if(passing != 0)pthread_cond_wait(&karsi2[carDir],&mute);
							//cout<<"halletti\n";
							kilit = false;
							changed = false;
							//if(changed)
							pthread_cond_broadcast(&siraa[curDir]);
							a = true;
							for(int k=0; k<4; k++) pthread_cond_broadcast(&karsi[k]);
							timeFlag[carDir] = !timeFlag[carDir];
						}
						
						else{
							//cout<< carId<< " else elsede\n";
							pthread_cond_wait(&siraa[carDir], &mute);
						}
					}

					goto begin;
				}

				pthread_mutex_unlock(&mute);

		}
    
};

vector<NarrowBridge> narrowBridgesMonitors;
vector<Ferry> ferriesMonitors;
vector<CrossRoad> crossRoadsMonitors; 
vector<Car> Cars;




void* HandleCars(void* arg){
	//Thread wakes up here
	Car* car = static_cast<Car*>(arg);
	for(int j=0; j<car->path.size();j++){ //HEr arabanın yolları tek tek
		string roadType = car->path[j][0].substr(0,1); //N0, F1 etc
		int roadId = stoi(car->path[j][0].substr(1,car->path[j][0].size()-1));
		int from = stoi(car->path[j][1]);
		int to = stoi(car->path[j][2]);
		

		if(roadType == "N") {
			//printf("roadID= %d \n", roadId);
			WriteOutput(car->id, roadType[0],roadId,TRAVEL);
			sleep_milli(car->travelTime);
			
			narrowBridgesMonitors[roadId].PassPassage(car->id,from,roadId);
		}
		else if(roadType =="F") {//PassFerry();
			WriteOutput(car->id, roadType[0],roadId,TRAVEL);
			sleep_milli(car->travelTime);
			WriteOutput(car->id, 'F',roadId,ARRIVE);
			ferriesMonitors[roadId].PassPassage(car->id,from,roadId);
			
			}
			
			
			
		else if(roadType == "C"){ 
			WriteOutput(car->id, roadType[0],roadId,TRAVEL);
			sleep_milli(car->travelTime);
			crossRoadsMonitors[roadId].PassPassage(car->id,from,roadId);}
		
	
	}
	

	return nullptr;
}

int main(){
	
	cin>>nbNum;
	
	narrowBridges.resize(nbNum);
	for(int i=0; i<nbNum;i++){
		narrowBridges[i].resize(2);
		cin>>narrowBridges[i][0];
		cin>>narrowBridges[i][1];
		NarrowBridge nb;
		narrowBridgesMonitors.push_back(nb);
	}
	cin>>fNum;
	
	ferries.resize(fNum);
	for(int i=0; i<fNum;i++){
		ferries[i].resize(3);
		cin>>ferries[i][0];
		cin>>ferries[i][1];
		cin>>ferries[i][2];
		Ferry nb;
		ferriesMonitors.push_back(nb);
	}
	
	cin>>crNum;
	crossRoads.resize(crNum);
	for(int i=0; i<crNum;i++){
		crossRoads[i].resize(2);
		cin>>crossRoads[i][0];
		cin>>crossRoads[i][1];
		CrossRoad nb;
		crossRoadsMonitors.push_back(nb);
	}
	
	cin>>carNum;
	Cars.resize(carNum);
	for(int i=0; i<carNum; i++){
		Car car;
		int pathLength;
		cin>>car.travelTime;
		cin>>pathLength;
		car.id=i;
		car.path.resize(pathLength);
		for(int j=0; j<pathLength; j++){
			car.path[j].resize(3);
			cin>>car.path[j][0];
			cin>>car.path[j][1];
			cin>>car.path[j][2];
		
		}
		Cars[i] = car;
	}
	
	
	
	vector<pthread_t> threads;
	for(int i=0; i<Cars.size();i++){
		InitWriteOutput();
		pthread_t tid;
		pthread_create(&tid,nullptr, HandleCars, &Cars[i]);
		threads.push_back(tid);
	
	}
	
	for(int i=0; i<threads.size(); i++) pthread_join(threads[i],nullptr);
	
	
	return 0;

}
