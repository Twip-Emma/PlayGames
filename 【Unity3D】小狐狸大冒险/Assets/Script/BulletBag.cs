using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletBag : MonoBehaviour
{
    public int bulletCount = 4;//可以增加的子弹数量

    public AudioClip bulletClip; //拾取子弹音效
    void OnTriggerEnter2D(Collider2D other){
        角色移动 pc = other.GetComponent<角色移动>();
        if(pc != null){
            if(pc.MyCurBulletCount < pc.MyMaxBulletCount){
                pc.ChangeBulletCount(bulletCount);//增加玩家子弹
                AudioManager.instance.AudioPlay(bulletClip);
                Destroy(this.gameObject);
            }
        }    
    }
}
